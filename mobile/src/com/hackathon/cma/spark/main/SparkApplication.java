package com.hackathon.cma.spark.main;

import android.app.Application;
import android.content.Context;
import android.graphics.Typeface;

public class SparkApplication extends Application {
    
    private static Context context;
    
    private Typeface font;
    
    private static SparkApplication singleton;
    
    
    public static SparkApplication getInstance() {
        return singleton;
    }
    
    public static Context getAppContext()   {
        return context;
    }
    
    public Typeface getFontAwesome() {
        return font;
    }
    
    @Override
    public void onCreate() {
        super.onCreate();
        singleton = this;
        context = getApplicationContext();
        font = Typeface.createFromAsset(getAssets(), "fontawesome-webfont.ttf");
    }
}
