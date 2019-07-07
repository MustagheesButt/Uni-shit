import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Dashboard extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        PrintWriter out = res.getWriter();
        RequestDispatcher view = req.getRequestDispatcher("dashboard.jsp");
        HttpSession sess = req.getSession();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();

            ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE id = " + sess.getAttribute("user_id"));
            rs.next();
            req.setAttribute("user_cash", rs.getInt("cash"));

            rs = statement.executeQuery("SELECT * FROM stocks WHERE user_id = " + sess.getAttribute("user_id"));
            
            Integer total = 0;
            List<StockModel> stocks = new ArrayList<StockModel>();
            
            while (rs.next()) {
                total += rs.getInt("quantity");
                stocks.add(new StockModel(rs.getInt("user_id"), rs.getString("symbol"), rs.getInt("quantity")));
            }

            req.setAttribute("total_stock", total);
            req.setAttribute("stocks_data", stocks);
        } catch(Exception e) {
            out.println(e);
            return;
        }

        view.forward(req, res);
    }
}