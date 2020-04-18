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
		textArea.append("���� �̸�: "+client.getInetAddress().getHostName());
		input = new DataInputStream(client.getInputStream());
		output = new DataOutputStream(client.getOutputStream());
		textArea.append("\n����� ��Ʈ�� ����\n");
		textArea.append("������ ���� �޽���: "+input.readUTF());
		textArea.append("\nŬ���̾�Ʈ�� ������ �޽���: �����մϴ�.\n");
		output.writeUTF("�����մϴ�.");
		textArea.append("������ �����Ѵ�.\n");
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
		textArea.setFont(new Font("���� ����� 250", Font.PLAIN, 25));
		textArea.setLineWrap(true);
		textArea.setWrapStyleWord(true);
		add(textArea);
		String file_name = "�Ѹ���.txt";
		
		/*
		JScrollPane scroll = new JScrollPane (textArea);
		scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		      scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		add(scroll);
		*/
		
		//���
		
		
		list_meues.add("ȭ��Ʈ ��������");
		list_meues.add("�𷰽��Ұ�����");
		list_meues.add("���̹���");
		list_meues.add("�Ҹ��Ǵ�������");
		list_meues.add("ȭ��Ʈ��������set");
		list_meues.add("�𷰽��Ұ�����set");
		list_meues.add("���̹���set");
		list_meues.add("�Ҹ��Ǵ������� set");
		list_meues.add("�������ܺ�");
		list_meues.add("�����ؾ�䰨��");
		list_meues.add("�ܼ�����");
		list_meues.add("����ġ�");
		list_meues.add("ġ�ƽ");
		list_meues.add("�ݶ�");
		list_meues.add("���̴�");
		list_meues.add("����ƾ��");
		
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
		
		JButton button_17 = new JButton("�� �� �� ��");
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
		button_17.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_17.setBounds(50, 37, 150, 50);
		add(button_17);
		
		JButton btnNewButton = new JButton("��  ��");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.setText("");  //textArea reset
				Sum_price = 0;
			}
		});
		btnNewButton.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		btnNewButton.setBounds(786, 37, 190, 70);
		add(btnNewButton);		
		
		//����
		JButton button_2 = new JButton("�� ��");
		button_2.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_2.setBounds(378, 37, 190, 70);
		add(button_2);
		//button_2.addActionListener(new DialogListener());
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			
				 int response = JOptionPane.showConfirmDialog(null, "�����Ͻðڽ��ϱ�?", "�� ��",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
				if(response == JOptionPane.YES_OPTION){
					String po = "����";
					textArea.append("              "+po+"\n");
				} else {
					textArea.setText("");
				}
			}
		});
		
		//���
		JButton button = new JButton("��  ��");
		button.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button.setBounds(582, 37, 190, 70);
		add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
			 String S_time = t.getString();
				int response = JOptionPane.showConfirmDialog(null,"���� �ݾ� " + Sum_price +"�� �Դϴ�.\n"+ "���� �Ͻðڽ��ϱ�?" , "��  ��",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
				String data = S_time+" " + " / �Ǹűݾ�= "+ Sum_price+"��\n";
				 if(response == JOptionPane.YES_OPTION){
					try {
						writer = new FileWriter(file_name);
						writer.write(data);
						
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					
					 JOptionPane.showMessageDialog(null, "���� �Ϸ� �ƽ��ϴ�.", "�� �� �� ��", JOptionPane.OK_OPTION);
					 textArea.setText("");
					 Sum_price=0;
				} else {
					textArea.setText("");
					Sum_price=0;
				}
			}
		});
		
		// �޴�
		JLabel label = new JLabel("�� ��");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setFont(new Font("���� ����� 250", Font.PLAIN, 30));
		label.setBounds(126, 136, 110, 38);
		add(label);
		
		//�����
		JLabel lblTake = new JLabel("�����");
		lblTake.setHorizontalAlignment(SwingConstants.CENTER);
		lblTake.setFont(new Font("���� ����� 250", Font.PLAIN, 30));
		lblTake.setBounds(700, 136, 198, 38);
		add(lblTake);
		
		// �ݾ�
		JLabel label_2 = new JLabel("�� ��");
		label_2.setHorizontalAlignment(SwingConstants.CENTER);
		label_2.setFont(new Font("���� ����� 250", Font.PLAIN, 30));
		label_2.setBounds(430, 136, 110, 38);
		add(label_2);
		
		//��ǰ - ȭ��Ʈ��������
		JButton btnNewButton_1 = new JButton("ȭ��Ʈ��������");
		btnNewButton_1.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue = list_meues.get(0).toString();
				int price = list_price.get(0);
				textArea.append("         " + meue + "                  " + price +" ��"+"\n");
				Sum_price = Sum_price + price;
			}
		});
		btnNewButton_1.setBounds(16, 523, 220, 70);
		add(btnNewButton_1);
		
		//��ǰ - �𷰽��Ұ�����
		JButton button_3 = new JButton("�𷰽��Ұ�����");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String meue2 = list_meues.get(1).toString();
				int price2 =list_price.get(1);
				textArea.append("       " + meue2 + "                   " + price2 +" ��"+"\n");
				Sum_price = Sum_price + price2;
			}
		});
		button_3.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_3.setBounds(258, 523, 220, 70);
		add(button_3);
		
		//��ǰ - ���̹���
		JButton button_4 = new JButton("���̹���");
		button_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String meue3 =  list_meues.get(2).toString();
				int price3 = list_price.get(2);
				textArea.append("            " + meue3 + "                        " + price3 +" ��"+"\n");
				Sum_price = Sum_price + price3;
			}
		});
		button_4.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_4.setBounds(500, 523, 220, 70);
		add(button_4);
		
		//��ǰ - �Ҹ��Ǵ�������
		JButton button_5 = new JButton("�Ҹ��Ǵ�������");
		button_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String meue4 = list_meues.get(3).toString();
				int price4 =  list_price.get(3);
				textArea.append("       " + meue4 + "                   " + price4 +" ��"+"\n");
				Sum_price = Sum_price + price4;
			}
		});
		button_5.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_5.setBounds(742, 523, 220, 70);
		add(button_5);
		
		//��Ʈ - ȭ��Ʈ��������
		JButton button_1 = new JButton("ȭ��Ʈ��������SET");
		button_1.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_1.setBounds(16, 624, 220, 70);
		add(button_1);
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"�ݶ�", "���̴�", "����ƾ��"};
				String mene5 = list_meues.get(4).toString();
				int price5 = list_price.get(4);
				int response2 = JOptionPane.showOptionDialog(null, "������� �����Ͻðڽ��ϱ�?", "���������",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("     " + mene5 + "                  " + price5 +" ��"+ "                          " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 =list_meues.get(14).toString();
					textArea.append("     " + mene5 + "                  " + price5 +" ��"+ "                          " + mm2 +"\n");
				} else {
					String mm3 =list_meues.get(15).toString();
					textArea.append("     " + mene5 + "                  " + price5 +" ��"+ "                          " + mm3 +"\n");
				}
				Sum_price = Sum_price + price5;
			}
		});
		
		//��Ʈ - �𷰽��Ұ�����
		JButton button_6 = new JButton("�𷰽��Ұ�����SET");
		button_6.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_6.setBounds(258, 624, 220, 70);
		add(button_6);
		button_6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"�ݶ�", "���̴�", "����ƾ��"};
				String mene6 =list_meues.get(5).toString();
				int price6 = list_price.get(5);
				int response2 = JOptionPane.showOptionDialog(null, "������� �����Ͻðڽ��ϱ�?", "���������",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("     " + mene6 + "               " + price6 +" ��"+ "                          " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 = list_meues.get(14).toString();
					textArea.append("     " + mene6 + "               " + price6 +" ��"+ "                          " + mm2 +"\n");
				} else {
					String mm3 =list_meues.get(15).toString();
					textArea.append("     " + mene6 + "               " + price6 +" ��"+ "                          " + mm3 +"\n");
				}
				Sum_price = Sum_price + price6;
			}
		});
		
		//��Ʈ - ���̹���
		JButton button_7 = new JButton("���̹���SET");
		button_7.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_7.setBounds(500, 624, 220, 70);
		add(button_7);
		button_7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"�ݶ�", "���̴�", "����ƾ��"};
				String mene7 = list_meues.get(6).toString();
				int price7 =  list_price.get(6);
				 int response2 = JOptionPane.showOptionDialog(null, "������� �����Ͻðڽ��ϱ�?", "���������",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("          " + mene7 + "                    " + price7 +" ��"+ "                          " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 = list_meues.get(14).toString();
					textArea.append("          " + mene7 + "                    " + price7 +" ��"+ "                          " + mm2 +"\n");
				} else {
					String mm3 = list_meues.get(15).toString();
					textArea.append("          " + mene7 + "                    " + price7 +" ��"+ "                          " + mm3 +"\n");
				}
				Sum_price = Sum_price + price7;
			}
		});
		
		//��Ʈ - �Ҹ��Ǵ�������
		JButton button_8 = new JButton("�Ҹ��Ǵ�������SET");
		button_8.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_8.setBounds(742, 625, 220, 70);
		add(button_8);
		button_8.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Object stringArray[] = {"�ݶ�", "���̴�", "����ƾ��"};
				String mene8 =list_meues.get(7).toString();
				int price8 = list_price.get(7);
				 int response2 = JOptionPane.showOptionDialog(null, "������� �����Ͻðڽ��ϱ�?", "���������",
					        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, stringArray, stringArray[2]);
				if(response2 == JOptionPane.YES_OPTION){
					String mm = list_meues.get(13).toString();
					textArea.append("    " + mene8 + "                " + price8 +" ��"+ "                         " + mm +"\n");
				} else if(response2 == JOptionPane.NO_OPTION){
					String mm2 =list_meues.get(14).toString();
					textArea.append("    " + mene8 + "                " + price8 +" ��"+ "                         " + mm2 +"\n");
				} else {
					String mm3 = list_meues.get(15).toString();
					textArea.append("    " + mene8 + "                " + price8 +" ��"+ "                         " + mm3 +"\n");
				}
				Sum_price = Sum_price + price8;
			}
		});
		
		//�������ܺ�
		JButton button_9 = new JButton("�������ܺ�");
		button_9.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_9.setBounds(16, 731, 220, 70);
		add(button_9);
		button_9.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue9 = list_meues.get(8).toString();
				int price9 = list_price.get(8);
				textArea.append("           " + meue9 + "                      " + price9 +" ��"+"\n");
				Sum_price = Sum_price + price9;
			}
		});
		
		//�����ؾ�䰨��
		JButton button_10 = new JButton("�����ؾ�䰨��");
		button_10.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_10.setBounds(258, 731, 220, 70);
		add(button_10);
		button_10.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue10 = list_meues.get(9).toString();
				int price10 =  list_price.get(9);
				textArea.append("         " + meue10 + "                   " + price10 +" ��"+"\n");
				Sum_price = Sum_price + price10;
			}
		});
		
		//�ܻ�����
		JButton button_11 = new JButton("�ܻ�����");
		button_11.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_11.setBounds(500, 731, 220, 70);
		add(button_11);
		button_11.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue11 = list_meues.get(10).toString();
				int price11 = list_price.get(10);
				textArea.append("            " + meue11 + "                        " + price11 +" ��"+"\n");
				Sum_price = Sum_price + price11;
			}
		});
		
		//����ġ�
		JButton button_12 = new JButton("����ġ�");
		button_12.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_12.setBounds(742, 731, 220, 70);
		add(button_12);
		button_12.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue12 = list_meues.get(11).toString();
				int price12 =  list_price.get(11);
				textArea.append("          " + meue12 + "                     " + price12 +" ��"+"\n");
				Sum_price = Sum_price + price12;
			}
		});
		
		//ġ�ƽ
		JButton button_13 = new JButton("ġ�ƽ");
		button_13.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_13.setBounds(16, 838, 220, 70);
		add(button_13);
		button_13.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue13 =list_meues.get(12).toString();
				int price13 = list_price.get(12);
				textArea.append("             " + meue13 + "                       " + price13 +" ��"+"\n");
				Sum_price = Sum_price + price13;
			}
		});
		
		//�ݶ�
		JButton button_14 = new JButton("�� ��");
		button_14.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_14.setBounds(258, 838, 220, 70);
		add(button_14);
		button_14.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue14 =list_meues.get(13).toString();
				int price14 =  list_price.get(13);
				textArea.append("               " + meue14 + "                          " + price14 +" ��"+"\n");
				Sum_price = Sum_price + price14;
			}
		});
		
		//���̴�
		JButton button_15 = new JButton("���̴�");
		button_15.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_15.setBounds(500, 838, 220, 70);
		add(button_15);
		button_15.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue15 =list_meues.get(14).toString();
				int price15 =list_price.get(14);
				textArea.append("             " + meue15 + "                         " + price15 +" ��"+"\n");
				Sum_price = Sum_price + price15;
			}
		});
		
		//����ƾ��
		JButton button_16 = new JButton("����ƾ��");
		button_16.setFont(new Font("���� ����� 250", Font.PLAIN, 20));
		button_16.setBounds(742, 838, 220, 70);
		add(button_16);
		button_16.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String meue16 = list_meues.get(15).toString();
				int price16 = list_price.get(15);;
				textArea.append("            " + meue16 + "                        " + price16 +" ��"+"\n");
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

