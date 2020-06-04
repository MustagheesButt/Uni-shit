import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;

public class Register extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        RequestDispatcher view = req.getRequestDispatcher("register.jsp");
        view.forward(req, res);
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String name     = req.getParameter("name");
        String email    = req.getParameter("email");
        String password = req.getParameter("password");

        PrintWriter out = res.getWriter();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();

            int affectedRows = statement.executeUpdate("INSERT INTO users (email, name, password) VALUES ('" +
                                             email +
                                             "', '" + name +
                                             "', '" + password +
                                             "')", Statement.RETURN_GENERATED_KEYS);
            
            if (affectedRows == 1) {
                ResultSet rs = statement.getGeneratedKeys();
                rs.next();
                HttpSession sess = req.getSession();
                sess.setAttribute("user_id", rs.getInt(1));
                sess.setAttribute("user_name", name);
                rs.close();
                
                res.sendRedirect("dashboard");
            }
            else
                res.sendRedirect("register?email");
        } catch(Exception e) {
            out.println(e);
        }
    }
}