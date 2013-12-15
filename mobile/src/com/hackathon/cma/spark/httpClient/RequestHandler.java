package com.hackathon.cma.spark.httpClient;

import android.util.Log;

import com.hackathon.cma.spark.models.BaseModel;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpDelete;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpRequestBase;
import org.apache.http.client.utils.URLEncodedUtils;
import org.apache.http.entity.mime.HttpMultipartMode;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

public class RequestHandler {

    private static final String TAG = "RequestHandler";
    
    public HttpResponse get(String uri, ArrayList<NameValuePair> params) throws ClientProtocolException, IOException, RequestFailedException {
        if(params != null) {
            String paramString = URLEncodedUtils.format(params, "utf-8");
            uri += "?" + paramString;
        }
        HttpGet get = new HttpGet(uri);
        HttpResponse resp = exectuteHttpRequest(get);
        return resp;
    }
    
    public HttpResponse post(String url, int id, ArrayList<NameValuePair> params, BaseModel model) throws ClientProtocolException, IOException, IllegalStateException, RequestFailedException {
        HttpPost post = new HttpPost(url);
        if (params != null)
            post.setEntity(new UrlEncodedFormEntity(params));
        return exectuteHttpRequest(post);
    }
    
    public HttpResponse post(String url, ArrayList<NameValuePair> params)  throws ClientProtocolException, IOException, IllegalStateException, RequestFailedException {
         HttpPost post = new HttpPost(url);
            if (params != null) {
                post.setEntity(new UrlEncodedFormEntity(params));
            }
            return exectuteHttpRequest(post);  
    }    
    
    public boolean delete(String url) throws ClientProtocolException, IOException, RequestFailedException {
        HttpDelete delete = new HttpDelete(url);
        HttpResponse resp = exectuteHttpRequest(delete);
        if(resp.getStatusLine().getStatusCode() == HttpStatus.SC_OK)
            return true;
        else
            return false;   
    }
    
    public void SendMultipartFile(String url, String filePath) throws UnsupportedEncodingException {
        Log.d(TAG, "UPLOAD: SendMultipartFile");
        ArrayList<NameValuePair> params = new ArrayList<NameValuePair>();
        params.add(new BasicNameValuePair("field_name", "field_photo"));
        HttpPost httppost = new HttpPost(url);
        httppost.setEntity(new UrlEncodedFormEntity(params));
        
        File file = new File(filePath);

        Log.d(TAG, "UPLOAD: setting up multipart entity");

        MultipartEntity mpEntity = new MultipartEntity(HttpMultipartMode.BROWSER_COMPATIBLE);
        Log.d(TAG, "UPLOAD: file length = " + file.length());
        Log.d(TAG, "UPLOAD: file exist = " + file.exists());

        try {
            mpEntity.addPart("files[attachment]", new FileBody(file, "application/octet"));
            mpEntity.addPart("field_name", new StringBody("field_photo"));
        } catch (UnsupportedEncodingException e1) {
            Log.d(TAG, "UPLOAD: UnsupportedEncodingException");
            e1.printStackTrace();
        }

        httppost.setEntity(mpEntity);
        Log.d(TAG, "UPLOAD: executing request: " + httppost.getRequestLine());
        Log.d(TAG, "UPLOAD: request: " + httppost.getEntity().getContentType().toString());

        HttpResponse response;
        try {
            Log.d(TAG, "UPLOAD: about to execute");
            response = exectuteHttpRequest(httppost);
            Log.d(TAG, "UPLOAD: executed");
            HttpEntity resEntity = response.getEntity();
            Log.d(TAG, "UPLOAD: respose code: " + response.getStatusLine().toString());
            if (resEntity != null) {
                Log.d(TAG, "UPLOAD: " + EntityUtils.toString(resEntity));
            }
            if (resEntity != null) {
                resEntity.consumeContent();
            }
        } catch (ClientProtocolException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (RequestFailedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    
    public HttpResponse exectuteHttpRequest(HttpRequestBase request) throws ClientProtocolException, IOException, RequestFailedException {
        // Add whatever header required for authentication
        request.addHeader("Authorization","Basic YWRtaW46YWRtaW4=");
        
        HttpClient client = DefaultHTTPClient.getHTTPCLIENTInstance();
        Log.d(TAG, "Http request to : " + request.getURI().toString());
        HttpResponse response = client.execute(request);
        if (response.getStatusLine().getStatusCode() == HttpStatus.SC_UNAUTHORIZED) {
            throw new RequestFailedException();
        }
        if (response.getStatusLine().getStatusCode() != HttpStatus.SC_OK) {
            Log.d(TAG, "Request Failed - URL:" + request.getURI().toString());
            Log.d(TAG, "Request failed - status: " + response.getStatusLine().getStatusCode());
            throw new RequestFailedException();
        }

        return response;
    }
    
}
