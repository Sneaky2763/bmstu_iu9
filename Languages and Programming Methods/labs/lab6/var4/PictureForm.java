import javax.swing.*;
import java.awt.*;

public class PictureForm {
    private JPanel mainPanel;
    private JSpinner arms;
    private JSpinner legs;
    private JLabel fieldarms;
    private JLabel fieldlegs;
    private CanvasPanel canvasPanel;
    private JButton colorButton;
    private JLabel colorchoose;

    public PictureForm() {
        mainPanel = new JPanel(new BorderLayout());
        canvasPanel = new CanvasPanel();

        JPanel controlPanel = new JPanel(new FlowLayout());
        fieldarms = new JLabel("Количество рук: ");
        controlPanel.add(fieldarms);
        arms = new JSpinner(new SpinnerNumberModel(2, 2, 100, 1));
        controlPanel.add(arms);
        fieldlegs = new JLabel("Количество ног: ");
        controlPanel.add(fieldlegs);
        legs = new JSpinner(new SpinnerNumberModel(2, 2, 100, 1));
        controlPanel.add(legs);
        colorchoose = new JLabel("Выбор цвета: ");
        controlPanel.add(colorchoose);
        colorButton = new JButton("Выбрать цвет");
        controlPanel.add(colorButton);

        mainPanel.add(controlPanel, BorderLayout.NORTH);
        mainPanel.add(canvasPanel, BorderLayout.CENTER);

        arms.addChangeListener(e -> updateCanvas());
        legs.addChangeListener(e -> updateCanvas());
        colorButton.addActionListener(e -> chooseColor());
    }

    private void chooseColor() {
        Color newColor = JColorChooser.showDialog(
                mainPanel,
                "Выберите цвет",
                canvasPanel.getColor());
        if (newColor != null) {
            canvasPanel.setColor(newColor);
            updateCanvas();
        }
    }

    private void updateCanvas() {
        canvasPanel.setArms((int)arms.getValue());
        canvasPanel.setLegs((int)legs.getValue());
        canvasPanel.repaint();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("PictureForm");
        frame.setContentPane(new PictureForm().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setSize(800, 600);
        frame.setVisible(true);
    }

    static class CanvasPanel extends JPanel {
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
}