package com.hackathon.cma.spark.tables;

import android.net.Uri;

public interface MunicipalityTable extends BaseTable{
    public static final String TABLE_NAME = "Municipalities";
    
    public static final String SQL = "create table "+TABLE_NAME+"(_id integer primary key autoincrement," +
    		" type text, name text, area real)";
    
    public static final Uri CONTENT_URI = Uri.parse("content://" +AUTHORITY+"/" + TABLE_NAME);

    public static final String[] projection = {
        "_id", "type", "name", "area"
    };

    public static final int _IDC = 0;

    public static final int TYPEC = 1;

    public static final int NAMEC = 2;

    public static final int AREAC = 4;
}
