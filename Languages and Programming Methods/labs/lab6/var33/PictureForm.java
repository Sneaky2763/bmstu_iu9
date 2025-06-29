import javax.swing.*;
import java.awt.*;

public class PictureForm {
    private JPanel mainPanel;
    private JButton onOffButton;
    private JLabel onOff;
    private JLabel colorChoose;
    private JButton colorButton;
    private CanvasPanel canvasPanel;
    private Color originalColor = Color.YELLOW;
    private boolean isBlack = false;

    public PictureForm() {
        mainPanel = new JPanel(new BorderLayout());
        canvasPanel = new CanvasPanel();
        canvasPanel.setColor(originalColor);

        JPanel controlPanel = new JPanel(new FlowLayout());
        onOff = new JLabel("Вкл/выкл:");
        controlPanel.add(onOff);
        onOffButton = new JButton("Выключить");
        controlPanel.add(onOffButton);
        colorChoose = new JLabel("Выбрать цвет");
        controlPanel.add(colorChoose);
        colorButton = new JButton("Выбрать");
        controlPanel.add(colorButton);

        mainPanel.add(controlPanel, BorderLayout.NORTH);
        mainPanel.add(canvasPanel, BorderLayout.CENTER);

        onOffButton.addActionListener(e -> changeState());
        colorButton.addActionListener(e -> chooseColor());
    }

    private void chooseColor() {
        Color newColor = JColorChooser.showDialog(
                mainPanel,
                "Выберите цвет",
                canvasPanel.getColor());
        if (newColor != null) {
            originalColor = newColor;
            if (!isBlack) {
                canvasPanel.setColor(newColor);
            }
            updateCanvas();
        }
    }

    private void updateCanvas() {
        canvasPanel.repaint();
    }

    private void changeState() {
        if (isBlack) {
            canvasPanel.setColor(originalColor);
            onOffButton.setText("Выключить");
        } else {
            canvasPanel.setColor(Color.BLACK);
            onOffButton.setText("Включить");
        }
        isBlack = !isBlack;
        updateCanvas();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("PictureForm");
        frame.setContentPane(new PictureForm().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.pack();
        frame.setVisible(true);
    }
}