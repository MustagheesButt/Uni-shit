import java.io.*;
import java.time.LocalDateTime;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;

public class Sell extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        RequestDispatcher view = req.getRequestDispatcher("sell.jsp");

        PrintWriter out = res.getWriter();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();
            HttpSession sess = req.getSession();

            ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE id = '" + sess.getAttribute("user_id") + "'");
            rs.next();
            req.setAttribute("current_cash", rs.getDouble("cash"));
            
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

            // verify and update stocks table
            ResultSet rs = statement.executeQuery("SELECT * FROM stocks WHERE user_id = " + user_id + " AND symbol='" + symbol + "'");
            rs.next();
            if (rs.getInt("quantity") < Integer.parseInt(quantity)) {
                res.sendRedirect("dashboard?sellFail");
            }

            statement.executeUpdate("UPDATE stocks SET quantity = quantity - " + quantity +
                                    " WHERE user_id=" + user_id + " AND symbol = '" + symbol + "'");

            // update user's cash
            statement.executeUpdate("UPDATE users SET cash = cash + " + total_bill + " WHERE id = " + user_id);
            
            // update transactions table
            statement.executeUpdate("INSERT INTO transactions (user_id, type, symbol, quantity, price, date) VALUES(" +
                                    user_id +
                                    ", 'SELL'" +
                                    ", '" + symbol +
                                    "', " + quantity +
                                    ", " + price +
                                    ", '" + LocalDateTime.now() + "')");
            
            // redirect back to dashboard
            res.sendRedirect("dashboard?sellSuccess");
        } catch(Exception e) {
            out.println(e);
        }
    }
}