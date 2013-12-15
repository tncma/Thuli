
package com.hackathon.cma.spark.main;

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v4.app.FragmentActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import com.hackathon.cma.spark.R;
import com.hackathon.cma.spark.services.ServiceHelper;

import org.apache.http.entity.mime.MultipartEntity;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

public class CreateSparkActivity extends FragmentActivity {
    
    private static final String TAG = "CreateSparkActivity";
    
    private static final int TAKE_PICTURE_ACTION = 10;
    
    private TextView mSubjectTv;
    
    private TextView mBodyTv;
    
    private ImageButton mPicButton;
    
    private String mCurrentImagePath;
    

    @Override
    protected void onCreate(Bundle arg0) {
        setContentView(R.layout.create_thuli);
        mSubjectTv = (TextView)findViewById(R.id.thuliSubject);
        mBodyTv = (TextView)findViewById(R.id.thuliBody);
        mPicButton = (ImageButton)findViewById(R.id.thuliImage);
        mPicButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                dispatchTakePictureIntent(TAKE_PICTURE_ACTION);
            }
        });
        super.onCreate(arg0);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if(menu != null) menu.clear();
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.create_spark, menu);
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if(item.getItemId() == R.id.send_thuli) {
            sendThuli();
        }
        return true;
    }
    
    private void dispatchTakePictureIntent(int actionCode) {
        if(isIntentAvailable(getApplicationContext(), MediaStore.ACTION_IMAGE_CAPTURE)) {
            try {
                Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                File f = createImageFile();
                takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(f));
                startActivityForResult(takePictureIntent, actionCode);
            } catch (IOException e) {
                Log.e(TAG, Log.getStackTraceString(e));
            }
        } else {
            Toast.makeText(getApplicationContext(), R.string.no_camera, Toast.LENGTH_LONG).show();
        }
    }
    
    public static boolean isIntentAvailable(Context context, String action) {
        final PackageManager packageManager = context.getPackageManager();
        final Intent intent = new Intent(action);
        List<ResolveInfo> list =
                packageManager.queryIntentActivities(intent, PackageManager.MATCH_DEFAULT_ONLY);
        return list.size() > 0;
        
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == TAKE_PICTURE_ACTION && resultCode == -1 && data != null) {
            Bundle extras = data.getExtras();
            if(extras != null && extras.get("data") != null) {
                Bitmap mImageBitmap = (Bitmap) extras.get("data");
                mPicButton.setImageBitmap(mImageBitmap);
            }
        }
        super.onActivityResult(requestCode, resultCode, data);
    }
    
    private String getAlbumName() {
        return getString(R.string.app_name);
    }
    
    private File getAlbumDir() {
        File storageDir = new File(
                Environment.getExternalStoragePublicDirectory(
                    Environment.DIRECTORY_PICTURES
                ), 
                getAlbumName()
            );
        if(!storageDir.exists()) {
            storageDir.mkdirs();
        }
        return storageDir;
    }
    
    private File createImageFile() throws IOException {
        // Create an image file name
        String timeStamp = 
            new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String imageFileName = getAlbumName() + timeStamp + "_" + ".jpg";
        File image = File.createTempFile(
            imageFileName, 
            getAlbumName(), 
            getAlbumDir()
        );
        mCurrentImagePath = image.getAbsolutePath();
        return image;
    }

    private void sendThuli() {
        if(validateThuli()) {
            Bundle b = new Bundle();
            b.putString("subject", mSubjectTv.getText().toString());
            b.putString("body", mBodyTv.getText().toString());
            b.putString("file", mCurrentImagePath);
            Intent serviceIntent = new Intent(CreateSparkActivity.this, ServiceHelper.class);
            serviceIntent.putExtra("cmd", 1);
            serviceIntent.putExtra(ServiceHelper.PARAMS, b);
            startService(serviceIntent);
        }
        
    }
    
    private boolean validateThuli() {
        boolean valid = true;
        if(TextUtils.isEmpty(mSubjectTv.getText())) {
            valid = false;
            mSubjectTv.setError(getString(R.string.subject_error));
        } 
        if(TextUtils.isEmpty(mBodyTv.getText())) {
            valid = false;
            mBodyTv.setError(getString(R.string.body_error));
        }
        
        return valid;
    }
    
}
