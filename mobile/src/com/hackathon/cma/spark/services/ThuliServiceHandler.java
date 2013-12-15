package com.hackathon.cma.spark.services;

import android.content.ContentResolver;
import android.text.TextUtils;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.hackathon.cma.spark.httpClient.RequestFailedException;
import com.hackathon.cma.spark.httpClient.RequestHandler;
import com.hackathon.cma.spark.models.Thuli;
import com.hackathon.cma.spark.parsers.ThuliParser;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.message.BasicNameValuePair;

import java.io.IOException;
import java.util.ArrayList;

public class ThuliServiceHandler {
    
    private ContentResolver cr;
    
    private RequestHandler mRequestHandler;
    
    private HttpResponse response;
    
    private ObjectMapper mapper;
    
    public ThuliServiceHandler() {
        mRequestHandler = new RequestHandler();
        mapper = new ObjectMapper();
    }
    
    public ArrayList<Thuli> getThuliList(String myThuli, String status, String municipality, String location) throws ClientProtocolException, IOException, RequestFailedException {
      ArrayList<NameValuePair> params = new ArrayList<NameValuePair>();
      params.add(new BasicNameValuePair("myThuli", myThuli));
      if(!TextUtils.isEmpty(status)) params.add(new BasicNameValuePair("status", status));
      if(!TextUtils.isEmpty(municipality)) params.add(new BasicNameValuePair("muni", municipality));
      if(!TextUtils.isEmpty(location)) params.add(new BasicNameValuePair("location", location));
     
      response = mRequestHandler.get(Endpoints.getThuliListUrl(), params);
      return ThuliParser.ParseThuligal(mapper.readTree(response.getEntity().getContent()));
    }
    
    
}
