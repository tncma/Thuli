package com.hackathon.cma.spark.utils;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.TextView;

import com.hackathon.cma.spark.main.SparkApplication;

public class FontAwesomeView extends TextView {

	public FontAwesomeView(Context context, AttributeSet attrs) {
		super(context, attrs);
		setTypeface(SparkApplication.getInstance().getFontAwesome());
	}

}
