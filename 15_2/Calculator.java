package com.example.java;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JTextField;
import java.awt.BorderLayout;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import com.example.java.CalculatorEngine;

public class Calculator {

	private JFrame frame;
	private JTextField textField;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Calculator window = new Calculator();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Calculator() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		CalculatorEngine ce = new CalculatorEngine();
		frame = new JFrame();
		frame.setBounds(100, 100, 472, 287);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		textField = new JTextField();
		textField.setBounds(12, 10, 315, 21);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		JButton btnNewButton = new JButton("7");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("7");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton.setBounds(12, 53, 97, 23);
		frame.getContentPane().add(btnNewButton);
		
		JButton btnNewButton_1 = new JButton("8");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("8");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_1.setBounds(121, 52, 97, 23);
		frame.getContentPane().add(btnNewButton_1);
		
		JButton btnNewButton_2 = new JButton("9");
		btnNewButton_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				ce.Enter("9");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_2.setBounds(230, 52, 97, 23);
		frame.getContentPane().add(btnNewButton_2);
		
		JButton btnNewButton_3 = new JButton("4");
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("4");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_3.setBounds(12, 98, 97, 23);
		frame.getContentPane().add(btnNewButton_3);
		
		JButton btnNewButton_4 = new JButton("5");
		btnNewButton_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("5");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_4.setBounds(121, 98, 97, 23);
		frame.getContentPane().add(btnNewButton_4);
		
		JButton btnNewButton_5 = new JButton("6");
		btnNewButton_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("6");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_5.setBounds(230, 98, 97, 23);
		frame.getContentPane().add(btnNewButton_5);
		
		JButton btnNewButton_6 = new JButton("1");
		btnNewButton_6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("1");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_6.setBounds(12, 143, 97, 23);
		frame.getContentPane().add(btnNewButton_6);
		
		JButton btnNewButton_7 = new JButton("2");
		btnNewButton_7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("2");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_7.setBounds(121, 143, 97, 23);
		frame.getContentPane().add(btnNewButton_7);
		
		JButton btnNewButton_8 = new JButton("3");
		btnNewButton_8.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("3");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnNewButton_8.setBounds(230, 143, 97, 23);
		frame.getContentPane().add(btnNewButton_8);
		
		JButton button = new JButton("0");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("0");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		button.setBounds(12, 188, 97, 23);
		frame.getContentPane().add(button);
		
		JButton button_1 = new JButton("/");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("/");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		button_1.setBounds(337, 53, 97, 23);
		frame.getContentPane().add(button_1);
		
		JButton button_2 = new JButton("*");
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("*");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		button_2.setBounds(337, 98, 97, 23);
		frame.getContentPane().add(button_2);
		
		JButton button_3 = new JButton("-");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("-");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		button_3.setBounds(337, 143, 97, 23);
		frame.getContentPane().add(button_3);
		
		JButton button_4 = new JButton("+");
		button_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("+");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		button_4.setBounds(337, 188, 97, 23);
		frame.getContentPane().add(button_4);
		
		JButton btnC = new JButton("C");
		btnC.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("C");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
		btnC.setBounds(230, 188, 97, 23);
		frame.getContentPane().add(btnC);
		JButton btnNewButton_9 = new JButton("=");
		btnNewButton_9.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ce.Enter("=");
				double d = ce.numberToDisplay();
				textField.setText(d + "");
			}
		});
	
		btnNewButton_9.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		btnNewButton_9.setBounds(121, 188, 97, 23);
		frame.getContentPane().add(btnNewButton_9);
		
		JButton button_5 = new JButton("<-");
		button_5.setBounds(337, 9, 97, 23);
		frame.getContentPane().add(button_5);
	}
}
