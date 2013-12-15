package com.hackathon.cma.spark.tables;

import android.net.Uri;

public interface LeaderboardTable extends BaseTable {
    public static final String TABLE_NAME = "Leaderboard";
    
    public static final String SQL = "create table " + TABLE_NAME +"(_id integer primary key autoincrement," +
    		" username text, location text, points integer)";
    
    public static final Uri CONTENT_URI = Uri.parse("content://" + AUTHORITY +"/" + TABLE_NAME);

    public static final String[] projection = {
        "_id", "username", "location", "points"
    };

    public static final int _IDC = 0;

    public static final int USERNAMEC = 1;

    public static final int LOCATIONC = 2;

    public static final int POINTSC = 4;
}