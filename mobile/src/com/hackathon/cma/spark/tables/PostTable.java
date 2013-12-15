
package com.hackathon.cma.spark.tables;

import android.net.Uri;

public interface PostTable extends BaseTable {
    public static final String TABLE_NAME = "Post";
    
    public static final String SQL = "create table " + TABLE_NAME + "(_id integer primary key autoincrement, subject text, body text,"
            + " location text, status text, flag text, username text, action_taken_by text)";
    
    public static final Uri CONTENT_URI = Uri.parse("content://" + AUTHORITY + "/" + TABLE_NAME);

    public static final String[] projection = {
        "_id", "subject", "body", "location", "status", "flag", "username", "action_taken_by"
    };

    public static final int _IDC = 0;

    public static final int SUBJECTC = 1;

    public static final int BODYC = 2;

    public static final int LOCATIONC = 3;

    public static final int STATUSC = 4;

    public static final int FLAGC = 5;

    public static final int USERNAMEC = 6;

    public static final int ACTION_BYC = 7;
}
