import java.awt.*;
import javax.swing.*; 
import java.io.File;
import java.awt.event.*;

public class hanhlinux {
	public static void main(String args[]){
		hanhlinux hanh = new hanhlinux();
		}	
	public hanhlinux() {
		String home = System.getProperty("user.home");
		String dir = home + "\\.kundata\\".trim();
		File f = new File(dir); 
		if (! f.isDirectory()) {
			f.mkdir();
			JOptionPane.showMessageDialog(null, "Add img1, img2, img3, img4 to " + dir); 
			System.exit(1);
			}
		else{
			String imgall[] = {"img1", "img2", "img3", "img4"};
			for (String img : imgall) {
				File imgfile = new File(dir + "\\" + img.trim());
				if (! imgfile.exists()) {
					JOptionPane.showMessageDialog(null, "Image file not found");
					System.exit(1);
					}
				}
			}
		int i = 0;
		JLabel label = new JLabel();
		
		label.addKeyListener(new KeyListener(){
			
			public void keyPressed(KeyEvent e) {
				
				}
			public void keyTyped(KeyEvent e) {}
			public void keyReleased(KeyEvent e) {}
				});
		JFrame frame = new JFrame(); 
		 
		frame.setAlwaysOnTop(true);
		frame.setSize(400, 400);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("kun");
		frame.setVisible(true);
		}
	}
