package com.hackathon.cma.spark.services;

import android.app.IntentService;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.hackathon.cma.spark.httpClient.RequestFailedException;
import com.hackathon.cma.spark.httpClient.RequestHandler;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.message.BasicNameValuePair;

import java.io.IOException;
import java.util.ArrayList;

public class ServiceHelper extends IntentService {
    
    private static final String TAG = "ServiceHelper";
    
    public static final String PARAMS = "spark.params";
    
    private int cmd;

    public ServiceHelper() {
        super("ServiceHelper");
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        try {
            cmd = intent.getIntExtra("cmd", -1);
            Bundle b = intent.getBundleExtra(PARAMS);
            RequestHandler requestHandler = new RequestHandler();
            switch (cmd) {
                case 1:
                    ArrayList<NameValuePair> params = new ArrayList<NameValuePair>();
                    params.add(new BasicNameValuePair("node[type]", "thuli"));
                    params.add(new BasicNameValuePair("node[title]", b.getString("subject")));
                    params.add(new BasicNameValuePair("node[body]", b.getString("body")));
                    params.add(new BasicNameValuePair("node[language]", "en"));
                    HttpResponse response = requestHandler.post(Endpoints.getCreateThuliUrl(), params);
                    
                    ObjectMapper mapper = new ObjectMapper();
                    JsonNode node = mapper.readTree(response.getEntity().getContent());
                    String file = b.getString("file");
                    if(!TextUtils.isEmpty(file) && node.path("nid").asInt(0) != 0) {
                        String nid = node.path("nid").asText();
                        requestHandler.SendMultipartFile(Endpoints.getAttachFileUrl(nid), file);
                    }
                    break;

                default:
                    break;
            }
            
        } catch (NullPointerException e) {
            Log.e(TAG, Log.getStackTraceString(e));
        } catch (ClientProtocolException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalStateException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (RequestFailedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
    }
    

}
