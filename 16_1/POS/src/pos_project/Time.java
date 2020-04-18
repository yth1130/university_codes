package pos_project;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.*;

public class Time extends Thread {
	public String disp;
	
	public void run(){
		while(true){
			Date dt = new Date();
			SimpleDateFormat sdf = new SimpleDateFormat("yyy-MM-dd HH:mm:ss");
			disp = sdf.format(dt);
		}
	}
	public String getString(){
		return disp;
	}
}
