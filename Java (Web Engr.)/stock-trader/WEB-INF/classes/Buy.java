import java.io.*;
import java.time.LocalDateTime;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;

public class Buy extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        RequestDispatcher view = req.getRequestDispatcher("buy.jsp");

        PrintWriter out = res.getWriter();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();
            HttpSession sess = req.getSession();

            ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE id = '" + sess.getAttribute("user_id") + "'");
            rs.next();
            req.setAttribute("current_cash", rs.getInt("cash"));
            
        } catch(Exception e) {
            out.println(e);
            return;
        }

        view.forward(req, res);
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        HttpSession session = req.getSession();

        String symbol    = req.getParameter("symbol");
        String price     = req.getParameter("price");
        String quantity  = req.getParameter("quantity");
        Integer user_id  = (Integer)session.getAttribute("user_id");
        Double total_bill = Double.parseDouble(price) * Integer.parseInt(quantity);
        PrintWriter out = res.getWriter();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();

            // verify and update user's cash
            ResultSet rs = statement.executeQuery("SELECT cash FROM users WHERE id = " + user_id);
            rs.next();
            if (rs.getDouble("cash") < total_bill) {
                res.sendRedirect("dashboard?buyFail");
            } else {
                statement.executeUpdate("UPDATE users SET cash = cash - " + total_bill + " WHERE id = " + user_id);
            }

            // update stocks table
            rs = statement.executeQuery("SELECT * FROM stocks WHERE user_id = '" +
                                                  user_id +
                                                  "' AND symbol = '" + symbol + "'");
            
            if (rs.next() == false) {
                statement.executeUpdate("INSERT INTO stocks (user_id, symbol, quantity) VALUES(" +
                                        user_id +
                                        ", '" + symbol +
                                        "', " + quantity + ")");
            } else {
                statement.executeUpdate("UPDATE stocks SET quantity = quantity + " + quantity +
                                        " WHERE user_id=" + user_id + " AND symbol = '" + symbol + "'");
            }
            
            // update transactions table
            statement.executeUpdate("INSERT INTO transactions (user_id, type, symbol, quantity, price, date) VALUES(" +
                                    user_id +
                                    ", 'BUY'" +
                                    ", '" + symbol +
                                    "', " + quantity +
                                    ", " + price +
                                    ", '" + LocalDateTime.now() + "')");
            
            // redirect back to dashboard
            res.sendRedirect("dashboard?buySuccess");
        } catch(Exception e) {
            out.println(e);
        }
    }
}