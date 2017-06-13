import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.io.*;
import java.util.*;

import javax.swing.*;

public class Drawer {

    // N * M board, with K grid lines in between
    // assert N < M
    static int N, M, K, DN, DM;
    final static int UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4;
    final static int dx[] = {0, 0, 1, 0, -1}, dy[] = {0, -1, 0, 1, 0};

    // table for the edges
    static int table[][];

    public static void readConfig() {
        readConfig("solution.txt");
    }

    public static void readConfig(String fName) {
        try {
            Scanner scanner = new Scanner(new FileInputStream(fName));
            N = scanner.nextInt(); M = scanner.nextInt(); K = scanner.nextInt();
            assert(N >= 1 && M >= 1 && K >= 0);
            DN = (N + 1) * K + N; DM = (M + 1) * K + M;
            table = new int[DN][DM];
            for (int i = 0; i < DN; i++)
                for (int j = 0; j < DM; j++)
                    table[i][j] = scanner.nextInt();
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.err.println("Make sure " + fName + " is in the same directory.");
            System.exit(0x12313);
        } catch (NoSuchElementException ne){
            System.err.println("Data in " + fName + " is not in valid format.");
            System.exit(0x132);
        }
    }

    static class MyCanvas extends JComponent{
        static Point mousePt;
        // offset from the upper left corner
        static int x = 30, y = 30;

        // half width of the terminals (square)
        static int hw = 5;

        static int size, lineGap;

        static int myScale = 1;

        private void drawSquareAt(Graphics g, int corX, int corY) {
            // g.setColor(Color.BLACK);
            // g.drawRect(corX - hw, corY + hw, hw << 1, hw << 1);
            g.setColor(Color.BLUE);
            g.fillRect(corX - hw, corY - hw, hw << 1, hw << 1);
        }

        private void drawCircleAt(Graphics g, int corX, int corY) {
            g.setColor(Color.RED);
            g.fillOval(corX - hw, corY - hw, hw << 1, hw << 1);
        }

        private void drawVerticals(Graphics g) {
            g.setColor(Color.LIGHT_GRAY);
            for (int i = 0; i <= M; i++)
                for (int k = 0; k <= K; k++)
                    g.drawLine(i * size + lineGap * k, 0,
                            i * size + lineGap * k, (N + 1) * size);
            g.drawLine(M * size + lineGap * (K + 1), 0,
                    M * size + lineGap * (K + 1), (N + 1) * size);
        }

        private void drawHorizontals(Graphics g) {
            g.setColor(Color.LIGHT_GRAY);
            for (int i = 0; i <= N; i++)
                for (int k = 0; k <= K; k++)
                    g.drawLine(0, i * size + lineGap * k,
                            (M + 1) * size, i * size + lineGap * k);
            g.drawLine(0, N * size + lineGap * (K + 1),
                    (M + 1) * size, N * size + lineGap * (K + 1));
        }

        private void drawTerminals(Graphics g) {
            // draw inner terminals
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= M; j++) {
                    g.setColor(Color.BLACK);
                    drawSquareAt(g, j * size, i * size);
                }

            // draw outer terminals
            for (int i = 0; i <= M; i++)
                for (int k = 0; k <= K; k++) {
                    if (i + k == 0) continue;
                    drawCircleAt(g, i * size + lineGap * k, 0);
                    drawCircleAt(g, i * size + lineGap * k, (N + 1) * size);
                }

            for (int i = 0; i <= N; i++)
                for (int k = 0; k <= K; k++) {
                    if (i + k == 0) continue;
                    drawCircleAt(g, 0, i * size + lineGap * k);
                    drawCircleAt(g, (M + 1) * size, i * size + lineGap * k);
                }
        }

        private void drawEdgeAt(Graphics2D g, int i, int j) {
            g.setColor(new Color(0, 100, 0));
            int Corx = size * ((j + 1) / (K + 1)) + lineGap * ((j + 1) % (K + 1));
            int Cory = size * ((i + 1) / (K + 1)) + lineGap * ((i + 1) % (K + 1));
            g.drawLine(Corx, Cory, Corx + lineGap * dx[table[i][j]], Cory + lineGap * dy[table[i][j]]);
        }

        private void drawRoutingEdges(Graphics g) {
            // draw the routing edges
            Graphics2D gd = (Graphics2D) g;
            gd.setStroke(new BasicStroke(3));
            for (int i = 0; i < DN; i++)
                for (int j = 0; j < DM; j++)
                    if (table[i][j] != 0)
                        drawEdgeAt(gd, i, j);
        }

        public void paint(Graphics g) {
            int scale = min(getWidth(), (getHeight() - 30) * (M + 1) / (N + 1)) * myScale;

            Graphics2D gd = (Graphics2D) g;
            gd.translate(x * myScale, y * myScale);

            g.setColor(Color.WHITE);
            g.fillRect(0, 0, getWidth(), getHeight());
            hw = min(4, scale / (M * 15));
            g.setColor(Color.BLACK);

            // average size of gaps
            size = (scale - 40) / (M + 1);
            lineGap = size / (K + 1);
            if (size < 0) return;

            drawVerticals(g);

            drawHorizontals(g);

            drawRoutingEdges(g);

            drawTerminals(g);
        }
    }

    public static void draw() {
        // Create a window for displaying
        JFrame window = new JFrame();
        window.setTitle("Grid Layout");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        int scale = 300;
        window.setBounds(30, 30, scale, scale);
        MyCanvas canvas = new MyCanvas();

        canvas.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                canvas.mousePt = e.getPoint();
            }

            @Override
            public void mouseClicked(MouseEvent e) {
                // System.out.println("I am clicked!");
                if (SwingUtilities.isLeftMouseButton(e)) {
                    canvas.x -= e.getX() / canvas.myScale;
                    canvas.y -= e.getY() / canvas.myScale;
                    canvas.myScale += 1;
                    System.out.println("I am clicked at this point " + canvas.x + " , " + canvas.y);
                } else {
                    canvas.myScale = 1;
                    canvas.x = 30;
                    canvas.y = 30;
                }
                canvas.repaint();
            }
        });

        JTextField inputField = new JTextField("solution.txt", 0);
        JButton readBtn = new JButton("Read!");
        readBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                readConfig(inputField.getText());
                canvas.repaint();
            }
        });
        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new BoxLayout(inputPanel, BoxLayout.LINE_AXIS));
        inputPanel.add(inputField);
        inputPanel.add(readBtn);

        window.add(Box.createVerticalStrut(10));
        window.add(canvas, BorderLayout.CENTER);
        window.add(inputPanel, BorderLayout.PAGE_END);

        // Create an Listener to handle rescaling event
        window.addComponentListener(new ComponentAdapter() {
            public void componentResized(ComponentEvent e) {
                canvas.repaint();
            }
        });
        window.setVisible(true);
    }

    static private int min(int a, int b) {
        return (a < b ? a : b);
    }

    public static void main(String[] a) {
        readConfig();
        draw();
    }
}
