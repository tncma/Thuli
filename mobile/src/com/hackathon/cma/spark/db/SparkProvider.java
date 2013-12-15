
package com.hackathon.cma.spark.db;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteQueryBuilder;
import android.net.Uri;

import com.hackathon.cma.spark.tables.BaseTable;
import com.hackathon.cma.spark.tables.LeaderboardTable;
import com.hackathon.cma.spark.tables.MunicipalityTable;
import com.hackathon.cma.spark.tables.PostTable;

import java.util.HashMap;

/**
 * Custom ContentProvider implementation for Thuli.
 * 
 * 
 * @see http://www.vogella.com/articles/AndroidSQLite/article.html
 *
 */
public class SparkProvider extends ContentProvider {
    
    private SparkSqlOpenHelper mSparkOpenHelper;
    
    private static final UriMatcher mUriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
    
    private static final HashMap<String, String> postsMap, leaderboardMap, municipalityMap;
    
    static {
        mUriMatcher.addURI(BaseTable.AUTHORITY, PostTable.TABLE_NAME, SparkTableIds.POSTS);
        mUriMatcher.addURI(BaseTable.AUTHORITY, PostTable.TABLE_NAME + "/#", SparkTableIds.POST_ID);
        mUriMatcher.addURI(BaseTable.AUTHORITY, LeaderboardTable.TABLE_NAME, SparkTableIds.LEADERBOARD);
        mUriMatcher.addURI(BaseTable.AUTHORITY, LeaderboardTable.TABLE_NAME + "/#", SparkTableIds.LEADERBOARD_ID);
        mUriMatcher.addURI(BaseTable.AUTHORITY, MunicipalityTable.TABLE_NAME, SparkTableIds.MUNICIPALITY);
        mUriMatcher.addURI(BaseTable.AUTHORITY, MunicipalityTable.TABLE_NAME + "/#", SparkTableIds.MUNICIPALITY_ID);
        
        postsMap = new HashMap<String, String>();
        for (String column : PostTable.projection) {
            postsMap.put(column, column);
        }
        
        leaderboardMap = new HashMap<String, String>();
        for(String column : LeaderboardTable.projection) {
            leaderboardMap.put(column, column);
        }
        
        municipalityMap = new HashMap<String, String>();
        for (String column : MunicipalityTable.projection) {
            municipalityMap.put(column, column);
        }
    }
    
    @Override
    public boolean onCreate() {
        mSparkOpenHelper = new SparkSqlOpenHelper(getContext());
        return true;
    }
    
    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs,
            String sortOrder) {
        SQLiteQueryBuilder queryBuilder = new SQLiteQueryBuilder();
        String id = null;

        final int match = mUriMatcher.match(uri);
        switch (match) {
            case SparkTableIds.POSTS:
                queryBuilder.setTables(PostTable.TABLE_NAME);
                queryBuilder.setProjectionMap(postsMap);
                break;
            case SparkTableIds.POST_ID:
                queryBuilder.setTables(PostTable.TABLE_NAME);
                queryBuilder.setProjectionMap(postsMap);
                id = uri.getPathSegments().get(1);
                queryBuilder.appendWhere("_id" + "=" + id);
                break;
            case SparkTableIds.LEADERBOARD:
                queryBuilder.setTables(LeaderboardTable.TABLE_NAME);
                queryBuilder.setProjectionMap(leaderboardMap);
                break;
            case SparkTableIds.LEADERBOARD_ID:
                queryBuilder.setTables(LeaderboardTable.TABLE_NAME);
                queryBuilder.setProjectionMap(leaderboardMap);
                id = uri.getPathSegments().get(1);
                queryBuilder.appendWhere("_id" + "=" + id);
                break;
            case SparkTableIds.MUNICIPALITY:
                queryBuilder.setTables(MunicipalityTable.TABLE_NAME);
                queryBuilder.setProjectionMap(municipalityMap);
                break;
            case SparkTableIds.MUNICIPALITY_ID:
                queryBuilder.setTables(MunicipalityTable.TABLE_NAME);
                queryBuilder.setProjectionMap(municipalityMap);
                id = uri.getPathSegments().get(1);
                queryBuilder.appendWhere("_id" + "=" + id);
            default:
                break;
        }
        
        final SQLiteDatabase db = mSparkOpenHelper.getReadableDatabase();
        Cursor cursor = queryBuilder.query(db, projection, selection, selectionArgs, null, null, sortOrder);
        cursor.setNotificationUri(getContext().getContentResolver(), uri);
        return cursor;
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        // TODO Auto-generated method stub
        return 0;
    }
    
    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public String getType(Uri uri) {
        // TODO Auto-generated method stub
        return null;
    }

}
