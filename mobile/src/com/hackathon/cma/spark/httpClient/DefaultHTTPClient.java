package com.hackathon.cma.spark.httpClient;


import org.apache.http.client.HttpClient;
import org.apache.http.conn.ClientConnectionManager;
import org.apache.http.conn.scheme.PlainSocketFactory;
import org.apache.http.conn.scheme.Scheme;
import org.apache.http.conn.scheme.SchemeRegistry;
import org.apache.http.conn.ssl.SSLSocketFactory;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.impl.conn.tsccm.ThreadSafeClientConnManager;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

public class DefaultHTTPClient {
	private static HttpClient HTTPCLIENT;
	
	public static HttpClient getHTTPCLIENTInstance() {
		if(HTTPCLIENT==null){
			//Create HttpClient for the application			
			SchemeRegistry schemeRegistry = new SchemeRegistry();					
			schemeRegistry.register(new Scheme("http", PlainSocketFactory.getSocketFactory(), 80));
			schemeRegistry.register(new Scheme("https", SSLSocketFactory.getSocketFactory(), 443));
			//HttpParams httpParams = new BasicHttpParams();
			//HttpConnectionParams.setConnectionTimeout(httpParams, 19000);
			//HttpConnectionParams.setSoTimeout(httpParams, 20000);			
			HttpParams parameters = new BasicHttpParams();
			HttpConnectionParams.setConnectionTimeout(parameters, 29000);		
			HttpConnectionParams.setSoTimeout(parameters, 30000);
			ClientConnectionManager connectionManager = new ThreadSafeClientConnManager(parameters, schemeRegistry);
			HTTPCLIENT = new DefaultHttpClient(connectionManager, parameters);
		}
		return HTTPCLIENT;
	}

	public static void disposeHTTPCLIENT() {
		HTTPCLIENT = null;
	}
	
}
