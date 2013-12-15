package com.hackathon.cma.spark.httpClient;

public class RequestFailedException extends Exception {

    /**
     * 
     */
    private static final long serialVersionUID = -670741921542552958L;

    @Override
    public String getMessage() {
        return "Request failed. Please try again later";
    }
}
