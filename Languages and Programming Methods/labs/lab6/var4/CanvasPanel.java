import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

class CanvasPanel extends JPanel {
    private int legs = 2;
    private int arms = 2;
    private Color color = Color.RED;

    public Color getColor() {
        return color;
    }
    public void setColor(Color color) {
        this.color = color;
    }
    public void setArms(int arms) {
        this.arms = arms;
    }
    public void setLegs(int legs) {
        this.legs = legs;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.setColor(color);
        int bodyX = 100;
        int bodyY = 500;
        int bodyWidth = 800;
        int bodyHeight = 200;
        g.fillRect(bodyX, bodyY, bodyWidth, bodyHeight);

        int headDiameter = 200;
        g.fillOval(bodyWidth, bodyY - headDiameter, headDiameter, headDiameter);


        int armLength = 80;
        int armStartX = bodyX + bodyWidth;
        for(int i = 0; i < arms; i++) {
            double position = (double)i/(arms-1);
            int startY = bodyY + (int)(bodyHeight * position);
            g.drawLine(armStartX, startY, armStartX + armLength, startY);
        }

        int legLength = 100;
        int legStartY = bodyY + bodyHeight;

        for (int i = 0; i < legs; i++) {
            double position = (double)i/(legs-1);
            int startX = bodyX + (int)(bodyWidth * position);
            g.drawLine(startX, legStartY, startX, legStartY + legLength);
        }
    }
}
