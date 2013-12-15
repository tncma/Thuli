
package com.hackathon.cma.spark.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.hackathon.cma.spark.tables.LeaderboardTable;
import com.hackathon.cma.spark.tables.MunicipalityTable;
import com.hackathon.cma.spark.tables.PostTable;

public class SparkSqlOpenHelper extends SQLiteOpenHelper {
    private static final String TAG = "SparkSqlOpenHelper";

    private static final String DB_NAME = "SparkDatabase";

    private static final int CURRENT_VERSION = 1;

    public SparkSqlOpenHelper(Context context) {
        // Use default cursor factory
        super(context, DB_NAME, null, CURRENT_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        Log.i(TAG, "Initiating creation of database");
        db.execSQL(PostTable.SQL);
        db.execSQL(LeaderboardTable.SQL);
        db.execSQL(MunicipalityTable.SQL);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // TODO Auto-generated method stub
    }
}
