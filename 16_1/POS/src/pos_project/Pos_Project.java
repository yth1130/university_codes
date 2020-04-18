package pos_project;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import java.util.List;
import java.io.*;
import java.net.*;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.awt.event.*;
import java.util.*;
import java.text.*;


class MyPos_Project extends JPanel implements ActionListener{

	JFrame frame;
	JTextArea textArea;
	public static List<String> list_meues =  new ArrayList<String>();
	public static List<Integer> list_price =  new ArrayList<Integer>();
	int Sum_price;
	Socket client;
	DataOutputStream output;
	DataInputStream input;
	Time t = new Time();
	FileWriter writer;
	
	
	
	
	public void runClent(){
		try{
		client = new Socket(InetAddress.getLocalHost(),5000);
		textArea.append("서버 이름: "+client.getInetAddress().getHostName());
		input = new DataInputStream(client.getInputStream());
		output = new DataOutputStream(client.getOutputStream());
		textArea.append("\n입출력 스트림 생성\n");
		textArea.append("서버가 보낸 메시지: "+input.readUTF());
		textArea.append("\n클라이언트가 보내는 메시지: 감사합니다.\n");
		output.writeUTF("감사합니다.");
		textArea.append("연결을 단절한다.\n");
		client.close();
		}catch (IOException e){
			e.printStackTrace();
		}
	}
	public MyPos_Project()  {
		
		t.start();
		
		setLayout(null);
		textArea = new JTextArea();
		textArea.setBounds(16, 186, 948, 306);
		textArea.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 25));
		textArea.setLineWrap(true);
		textArea.setWrapStyleWord(true);
		add(textArea);
		String file_name = "총매출.txt";
		
		/*
		JScrollPane scroll = new JScrollPane (textArea);
		scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		      scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		add(scroll);
		*/
		
		//취소
		
		
		list_meues.add("화이트 갈릭버거");
		list_meues.add("디럭스불고기버거");
		list_meues.add("싸이버거");
		list_meues.add("할리피뇨통살버거");
		list_meues.add("화이트갈릭버거set");
		list_meues.add("디럭스불고기버거set");
		list_meues.add("싸이버거set");
		list_meues.add("할리피뇨통살버거 set");
		list_meues.add("맘스팝콘볼");
		list_meues.add("케이준양념감자");
		list_meues.add("콘셀러드");
		list_meues.add("고구마치즈볼");
		list_meues.add("치즈스틱");
		list_meues.add("콜라");
		list_meues.add("사이다");
		list_meues.add("마운틴듀");
		
		list_price.add(4200);
		list_price.add(3800);
		list_price.add(3500);
		list_price.add(3800);
		list_price.add(5800);
		list_price.add(5700);
		list_price.add(5100);
		list_price.add(5500);
		list_price.add(2000);
		list_price.add(1700);
		list_price.add(1500);
		list_price.add(2000);
		list_price.add(1600);
		list_price.add(1300);
		list_price.add(1300);
		list_price.add(1300);
		
		JButton button_17 = new JButton("영 업 종 료");
		button_17.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				 try {
					writer.close();
					System.exit(0);
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		button_17.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_17.setBounds(50, 37, 150, 50);
		add(button_17);
		
		JButton btnNewButton = new JButton("취  소");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.setText("");  //textArea reset
				Sum_price = 0;
			}
		});
		btnNewButton.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		btnNewButton.setBounds(786, 37, 190, 70);
		add(btnNewButton);		
		
		//포장
		JButton button_2 = new JButton("포 장");
		button_2.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_2.setBounds(378, 37, 190, 70);
		add(button_2);
		//button_2.addActionListener(new DialogListener());
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			
				 int response = JOptionPane.showConfirmDialog(null, "포장하시겠습니까?", "포 장",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
				if(response == JOptionPane.YES_OPTION){
					String po = "포장";
					textArea.append("              "+po+"\n");
				} else {
					textArea.setText("");
				}
			}
		});
		
		//계산
		JButton button = new JButton("계  산");
		button.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button.setBounds(582, 37, 190, 70);
		add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
			 String S_time = t.getString();
				int response = JOptionPane.showConfirmDialog(null,"결제 금액 " + Sum_price +"원 입니다.\n"+ "결제 하시겠습니까?" , "결  제",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
				String data = S_time+" " + " / 판매금액= "+ Sum_price+"원\n";
				 if(response == JOptionPane.YES_OPTION){
					try {
						writer = new FileWriter(file_name);
						writer.write(data);
						
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					
					 JOptionPane.showMessageDialog(null, "결제 완료 됐습니다.", "결 제 완 료", JOptionPane.OK_OPTION);
					 textArea.setText("");
					 Sum_price=0;
				} else {
					textArea.setText("");
					Sum_price=0;
				}
			}
		});
		
		// 메뉴
		JLabel label = new JLabel("메 뉴");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 30));
		label.setBounds(126, 136, 110, 38);
		add(label);
		
		//음료수
		JLabel lblTake = new JLabel("음료수");
		lblTake.setHorizontalAlignment(SwingConstants.CENTER);
		lblTake.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 30));
		lblTake.setBounds(700, 136, 198, 38);
		add(lblTake);
		
		// 금액
		JLabel label_2 = new JLabel("금 액");
		label_2.setHorizontalAlignment(SwingConstants.CENTER);
		label_2.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 30));
		label_2.setBounds(430, 136, 110, 38);
		add(label_2);
		
		//단품 - 화이트갈릭버거
		JButton btnNewButton_1 = new JButton("화이트갈릭버거");
		btnNewButton_1.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue = list_meues.get(0).toString();
				int price = list_price.get(0);
				textArea.append("         " + meue + "                  " + price +" 원"+"\n");
				Sum_price = Sum_price + price;
			}
		});
		btnNewButton_1.setBounds(16, 523, 220, 70);
		add(btnNewButton_1);
		
		//단품 - 디럭스불고기버거
		JButton button_3 = new JButton("디럭스불고기버거");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String meue2 = list_meues.get(1).toString();
				int price2 =list_price.get(1);
				textArea.append("       " + meue2 + "                   " + price2 +" 원"+"\n");
				Sum_price = Sum_price + price2;
			}
		});
		button_3.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_3.setBounds(258, 523, 220, 70);
		add(button_3);
		
		//단품 - 싸이버거
		JButton button_4 = new JButton("싸이버거");
		button_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String meue3 =  list_meues.get(2).toString();
				int price3 = list_price.get(2);
				textArea.append("            " + meue3 + "                        " + price3 +" 원"+"\n");
				Sum_price = Sum_price + price3;
			}
		});
		button_4.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_4.setBounds(500, 523, 220, 70);
		add(button_4);
		
		//단품 - 할리피뇨통살버거
		JButton button_5 = new JButton("할리피뇨통살버거");
		button_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String meue4 = list_meues.get(3).toString();
				int price4 =  list_price.get(3);
				textArea.append("       " + meue4 + "                   " + price4 +" 원"+"\n");
				Sum_price = Sum_price + price4;
			}
		});
		button_5.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_5.setBounds(742, 523, 220, 70);
		add(button_5);
		
		//세트 - 화이트갈릭버거
		JButton button_1 = new JButton("화이트갈릭버거SET");
		button_1.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_1.setBounds(16, 624, 220, 70);
		add(button_1);
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"콜라", "사이다", "마운틴듀"};
				String mene5 = list_meues.get(4).toString();
				int price5 = list_price.get(4);
				int response2 = JOptionPane.showOptionDialog(null, "음료수를 선택하시겠습니까?", "음료수선택",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("     " + mene5 + "                  " + price5 +" 원"+ "                          " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 =list_meues.get(14).toString();
					textArea.append("     " + mene5 + "                  " + price5 +" 원"+ "                          " + mm2 +"\n");
				} else {
					String mm3 =list_meues.get(15).toString();
					textArea.append("     " + mene5 + "                  " + price5 +" 원"+ "                          " + mm3 +"\n");
				}
				Sum_price = Sum_price + price5;
			}
		});
		
		//세트 - 디럭스불고기버거
		JButton button_6 = new JButton("디럭스불고기버거SET");
		button_6.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_6.setBounds(258, 624, 220, 70);
		add(button_6);
		button_6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"콜라", "사이다", "마운틴듀"};
				String mene6 =list_meues.get(5).toString();
				int price6 = list_price.get(5);
				int response2 = JOptionPane.showOptionDialog(null, "음료수를 선택하시겠습니까?", "음료수선택",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("     " + mene6 + "               " + price6 +" 원"+ "                          " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 = list_meues.get(14).toString();
					textArea.append("     " + mene6 + "               " + price6 +" 원"+ "                          " + mm2 +"\n");
				} else {
					String mm3 =list_meues.get(15).toString();
					textArea.append("     " + mene6 + "               " + price6 +" 원"+ "                          " + mm3 +"\n");
				}
				Sum_price = Sum_price + price6;
			}
		});
		
		//세트 - 싸이버거
		JButton button_7 = new JButton("싸이버거SET");
		button_7.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_7.setBounds(500, 624, 220, 70);
		add(button_7);
		button_7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"콜라", "사이다", "마운틴듀"};
				String mene7 = list_meues.get(6).toString();
				int price7 =  list_price.get(6);
				 int response2 = JOptionPane.showOptionDialog(null, "음료수를 선택하시겠습니까?", "음료수선택",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("          " + mene7 + "                    " + price7 +" 원"+ "                          " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 = list_meues.get(14).toString();
					textArea.append("          " + mene7 + "                    " + price7 +" 원"+ "                          " + mm2 +"\n");
				} else {
					String mm3 = list_meues.get(15).toString();
					textArea.append("          " + mene7 + "                    " + price7 +" 원"+ "                          " + mm3 +"\n");
				}
				Sum_price = Sum_price + price7;
			}
		});
		
		//세트 - 할리피뇨통살버거
		JButton button_8 = new JButton("할리피뇨통살버거SET");
		button_8.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_8.setBounds(742, 625, 220, 70);
		add(button_8);
		button_8.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"콜라", "사이다", "마운틴듀"};
				String mene8 =list_meues.get(7).toString();
				int price8 = list_price.get(7);
				 int response2 = JOptionPane.showOptionDialog(null, "음료수를 선택하시겠습니까?", "음료수선택",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("    " + mene8 + "                " + price8 +" 원"+ "                         " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 =list_meues.get(14).toString();
					textArea.append("    " + mene8 + "                " + price8 +" 원"+ "                         " + mm2 +"\n");
				} else {
					String mm3 = list_meues.get(15).toString();
					textArea.append("    " + mene8 + "                " + price8 +" 원"+ "                         " + mm3 +"\n");
				}
				Sum_price = Sum_price + price8;
			}
		});
		
		//맘스팝콘볼
		JButton button_9 = new JButton("맘스팝콘볼");
		button_9.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_9.setBounds(16, 731, 220, 70);
		add(button_9);
		button_9.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue9 = list_meues.get(8).toString();
				int price9 = list_price.get(8);
				textArea.append("           " + meue9 + "                      " + price9 +" 원"+"\n");
				Sum_price = Sum_price + price9;
			}
		});
		
		//케이준양념감자
		JButton button_10 = new JButton("케이준양념감자");
		button_10.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_10.setBounds(258, 731, 220, 70);
		add(button_10);
		button_10.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue10 = list_meues.get(9).toString();
				int price10 =  list_price.get(9);
				textArea.append("         " + meue10 + "                   " + price10 +" 원"+"\n");
				Sum_price = Sum_price + price10;
			}
		});
		
		//콘샐러드
		JButton button_11 = new JButton("콘샐러드");
		button_11.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_11.setBounds(500, 731, 220, 70);
		add(button_11);
		button_11.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue11 = list_meues.get(10).toString();
				int price11 = list_price.get(10);
				textArea.append("            " + meue11 + "                        " + price11 +" 원"+"\n");
				Sum_price = Sum_price + price11;
			}
		});
		
		//고구마치즈볼
		JButton button_12 = new JButton("고구마치즈볼");
		button_12.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_12.setBounds(742, 731, 220, 70);
		add(button_12);
		button_12.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue12 = list_meues.get(11).toString();
				int price12 =  list_price.get(11);
				textArea.append("          " + meue12 + "                     " + price12 +" 원"+"\n");
				Sum_price = Sum_price + price12;
			}
		});
		
		//치즈스틱
		JButton button_13 = new JButton("치즈스틱");
		button_13.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_13.setBounds(16, 838, 220, 70);
		add(button_13);
		button_13.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue13 =list_meues.get(12).toString();
				int price13 = list_price.get(12);
				textArea.append("             " + meue13 + "                       " + price13 +" 원"+"\n");
				Sum_price = Sum_price + price13;
			}
		});
		
		//콜라
		JButton button_14 = new JButton("콜 라");
		button_14.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_14.setBounds(258, 838, 220, 70);
		add(button_14);
		button_14.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue14 =list_meues.get(13).toString();
				int price14 =  list_price.get(13);
				textArea.append("               " + meue14 + "                          " + price14 +" 원"+"\n");
				Sum_price = Sum_price + price14;
			}
		});
		
		//사이다
		JButton button_15 = new JButton("사이다");
		button_15.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_15.setBounds(500, 838, 220, 70);
		add(button_15);
		button_15.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue15 =list_meues.get(14).toString();
				int price15 =list_price.get(14);
				textArea.append("             " + meue15 + "                         " + price15 +" 원"+"\n");
				Sum_price = Sum_price + price15;
			}
		});
		
		//마운틴듀
		JButton button_16 = new JButton("마운틴듀");
		button_16.setFont(new Font("한컴 윤고딕 250", Font.PLAIN, 20));
		button_16.setBounds(742, 838, 220, 70);
		add(button_16);
		button_16.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue16 = list_meues.get(15).toString();
				int price16 = list_price.get(15);;
				textArea.append("            " + meue16 + "                        " + price16 +" 원"+"\n");
				Sum_price = Sum_price + price16;
			}
		});
		
		
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
  		
		ImageIcon Icon = new ImageIcon("burger.jpg");
		Image img = Icon.getImage();
		g.drawImage(img,0,0,getWidth(),getHeight(), this);	
	}

	public void actionPerformed(ActionEvent e){
		
 	}
}

public class Pos_Project extends JFrame{
	public Pos_Project(){
		
		try {
			UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
	    }  
		catch (Exception e) { }
		
		MyPos_Project pos = new MyPos_Project();
		getContentPane().add(pos);

		setTitle("YONSEI");
		setSize(1000, 1000);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		
	}
	
	public static void main(String args[]){
		new Pos_Project();
	}
	
}

