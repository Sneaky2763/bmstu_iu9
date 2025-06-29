import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;

public class Circles {
    private JPanel mainPanel;
    private JSpinner aSpinner;
    private JSpinner bSpinner;
    private JSpinner dSpinner;
    private CanvasPanel canvasPanel;
    private JButton drawButton;

    public Circles() {
        mainPanel = new JPanel(new BorderLayout());
        canvasPanel = new CanvasPanel();

        JPanel controlPanel = new JPanel(new GridLayout(2, 4, 5, 5));

        controlPanel.add(new JLabel("Радиус первой окружности:"));
        aSpinner = new JSpinner(new SpinnerNumberModel(100, 50, 500, 10));
        controlPanel.add(aSpinner);

        controlPanel.add(new JLabel("Радиус второй окружности:"));
        bSpinner = new JSpinner(new SpinnerNumberModel(100, 50, 500, 10));
        controlPanel.add(bSpinner);

        controlPanel.add(new JLabel("Расстояние:"));
        dSpinner = new JSpinner(new SpinnerNumberModel(50, 10, 500, 5));
        controlPanel.add(dSpinner);


        drawButton = new JButton("Пересечение");
        controlPanel.add(drawButton);

        mainPanel.add(controlPanel, BorderLayout.NORTH);
        mainPanel.add(canvasPanel, BorderLayout.CENTER);

        aSpinner.addChangeListener(e -> updateCanvas());
        bSpinner.addChangeListener(e -> updateCanvas());
        dSpinner.addChangeListener(e -> updateCanvas());
        drawButton.addActionListener(e -> drawInter());
    }

    private void drawInter() {
        canvasPanel.changeInter();
        updateCanvas();
    }

    private void updateCanvas() {
        canvasPanel.setA((int)aSpinner.getValue());
        canvasPanel.setB((int)bSpinner.getValue());
        canvasPanel.setD((int)dSpinner.getValue());
        canvasPanel.repaint();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Окружности");
        frame.setContentPane(new Circles().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setVisible(true);
    }

    static class CanvasPanel extends JPanel {
        private int a = 100;
        private int b = 100;
        private int d = 50;
        private int draw_inter=0;
        private Color circleColor = Color.RED;

        public void setA(int a) {
            this.a = a;
        }

        public void setB(int b) {
            this.b = b;
        }

        public void setD(int d) {
            this.d = d;
        }

        public void changeInter(){
            if(this.draw_inter==0){
                this.draw_inter=1;
            } else {
                this.draw_inter=0;
            }
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int centerX = getWidth() / 2;
            int centerY = getHeight() / 2;

            g2d.drawOval(centerX-d/2-a, centerY-a, 2*a, 2*a);
            g2d.drawOval(centerX+d/2-b, centerY-b, b*2, b*2);
            g2d.setColor(circleColor);

            if (draw_inter==1){
                Point2D[] intersections=calculateIntersections();

                g2d.setColor(Color.RED);
                for (Point2D p: intersections) {
                    if (p != null) {
                        int pointSize=8;
                        g2d.fillOval((int)p.getX() - pointSize/2, (int)p.getY() - pointSize/2, pointSize, pointSize);
                    }
                }
            }
        }

        private Point2D[] calculateIntersections() {
            int centerX=getWidth()/2;
            int centerY=getHeight()/2;
            double x1=centerX-d/2;
            double y1=centerY;
            double x2=centerX+d/2;
            double y2=centerY;

            double c=x2-x1;

            if (c > a + b || c < Math.abs(a - b)) {
                return new Point2D[0];
            }

            double a2=Math.pow(a, 2);
            double b2=Math.pow(b, 2);
            double c2=Math.pow(c, 2);

            double l=(a2-b2+c2)/(2*c);
            double h=Math.sqrt(a2-Math.pow(l, 2));

            double x3=l+(h/c)*(y2-y1)+x1;
            double y3=(l/c)*(y2-y1)-h+y1;

            double x4=l-(h/c)*(y2-y1)+x1;
            double y4=(l/c)*(y2-y1)+h+y1;

            return new Point2D[] {
                    new Point2D.Double(x3, y3),
                    new Point2D.Double(x4, y4)
            };
        }
    }
}