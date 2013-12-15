
package com.hackathon.cma.spark.fragments;

import android.app.Fragment;
import android.app.ListFragment;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListAdapter;

import com.commonsware.cwac.endless.EndlessAdapter;
import com.hackathon.cma.spark.R;
import com.hackathon.cma.spark.services.ThuliServiceHandler;

import java.util.ArrayList;

public class ExploreFragment extends ListFragment {
    
    private static final String TAG = "ExploreFragment";
    
    private ArrayList<ExploreFragment> items;
    
    public static Fragment newInstance(Bundle b) {
        Fragment frag = new Fragment();
        frag.setArguments(b);
        return frag;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.thuli_list, container, false);
    }
    
    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        items = new ArrayList<ExploreFragment>();
        super.onActivityCreated(savedInstanceState);
    }
    
    private class ExploreEndlessAdapter extends EndlessAdapter {

        public ExploreEndlessAdapter(Context context, ListAdapter wrapped, int pendingResource) {
            super(context, wrapped, pendingResource);
        }

        @Override
        protected void appendCachedData() {
            
            
        }
        
        @Override
        protected boolean onException(View pendingView, Exception e) {
            
            return super.onException(pendingView, e);
        }

        @Override
        protected boolean cacheInBackground() throws Exception {
            ThuliServiceHandler handler = new ThuliServiceHandler();
            return false;
        }
        
        
        
    }

}
