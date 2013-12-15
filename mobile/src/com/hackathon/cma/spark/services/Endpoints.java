package com.hackathon.cma.spark.services;

public class Endpoints {
    
    private static final String SCHEME = "http";
    private static final String BASE_PATH = SCHEME + "://thulidev.devcloud.acquia-sites.com/";
    private static final String REST_PATH = BASE_PATH + "api/";
    private static final String THULI_LIST_URL = REST_PATH + "thulis.json";
    private static final String GET_THULI_URL = REST_PATH + "node/%s.json";
    private static final String CREATE_THULI_URL = REST_PATH + "node.json";
    private static final String ATTACH_FILE_URL = REST_PATH + "node/%s/attach_file.json";
    private static final String VOTE_UP_URL = REST_PATH + "flag/flag.json";
    private static final String VOTE_DOWN_URL = REST_PATH + "flag/flag.json";
    private static final String GET_COMMENTS_URL = REST_PATH + "comment.json?parameters[nid]=%s";
    private static final String ADD_COMMENT_URL = REST_PATH + "/comment.json";
    private static final String COMMENT_COUNT_URL = REST_PATH + "comment/countAll.json";
    
    public static String getScheme() {
        return SCHEME;
    }
    public static String getBasePath() {
        return BASE_PATH;
    }
    public static String getRestPath() {
        return REST_PATH;
    }
    public static String getThuliListUrl() {
        return THULI_LIST_URL;
    }
    public static String getGetThuliUrl(String nid) {
        return String.format(GET_THULI_URL, nid);
    }
    public static String getCreateThuliUrl() {
        return CREATE_THULI_URL;
    }
    public static String getAttachFileUrl(String nid) {
        return String.format(ATTACH_FILE_URL, nid);
    }
    public static String getVoteUpUrl() {
        return VOTE_UP_URL;
    }
    public static String getVoteDownUrl() {
        return VOTE_DOWN_URL;
    }
    public static String getGetCommentsUrl(String nid) {
        return String.format(GET_COMMENTS_URL, nid);
    }
    public static String getAddCommentUrl() {
        return ADD_COMMENT_URL;
    }
    public static String getCommentCountUrl() {
        return COMMENT_COUNT_URL;
    }
    
    
    
}   
