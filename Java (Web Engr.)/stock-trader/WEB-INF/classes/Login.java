import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        RequestDispatcher view = req.getRequestDispatcher("login.jsp");
        view.forward(req, res);
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        HttpSession session = req.getSession();

        String email     = req.getParameter("email");
        String password  = req.getParameter("password");

        PrintWriter out = res.getWriter();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_trader", "root", "");
            Statement statement = conn.createStatement();

            ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE email = '" + email + "'");

            if (rs.next() == false) {
                res.sendRedirect("login?email=" + email); // wrong email
            } else {
                if (rs.getString("password").equals(password)) {
                    HttpSession sess = req.getSession();
                    sess.setAttribute("user_id", rs.getInt("id"));
                    sess.setAttribute("user_name", rs.getString("name"));

                    res.sendRedirect("dashboard");
                } else {
                    res.sendRedirect("login?password"); // wrong password
                }
            }
            
            
        } catch(Exception e) {
            out.println(e);
        }
    }
}