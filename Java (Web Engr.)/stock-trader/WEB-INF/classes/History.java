import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class History extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        PrintWriter out = res.getWriter();
        RequestDispatcher view = req.getRequestDispatcher("history.jsp");
        HttpSession sess = req.getSession();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();

            ResultSet rs = statement.executeQuery("SELECT * FROM transactions WHERE user_id = " + sess.getAttribute("user_id"));

            List<TransactionModel> transactions = new ArrayList<TransactionModel>();
            
            while (rs.next()) {
                transactions.add(new TransactionModel(rs.getInt("id"), rs.getString("type"),
                                 rs.getString("symbol"), rs.getInt("quantity"), rs.getDouble("price"),
                                 rs.getDate("date")
                                 ));
            }

            req.setAttribute("transactions_data", transactions);
        } catch(Exception e) {
            out.println(e);
            return;
        }

        view.forward(req, res);
    }
}