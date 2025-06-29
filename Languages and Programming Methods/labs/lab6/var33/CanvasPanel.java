import javax.swing.*;
import java.awt.*;

public class CanvasPanel extends JPanel {
    private Color color = Color.YELLOW;

    public Color getColor(){
        return color;
    }

    public void setColor(Color color){
        this.color=color;
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(color);
        g.fillOval(100, 100, 100, 100);
    }
}
