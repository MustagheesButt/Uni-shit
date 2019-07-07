import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;

public class Register extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        RequestDispatcher view = req.getRequestDispatcher("register.html");
        view.forward(req, res);
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String firstName = req.getParameter("firstName");
        String lastName  = req.getParameter("lastName");
        String email     = req.getParameter("email");
        String password  = req.getParameter("password");

        PrintWriter out = res.getWriter();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/uni_labs", "root", "");
            Statement statement = conn.createStatement();

            int rv = statement.executeUpdate("INSERT INTO users (email, first_name, last_name, password) VALUES ('" +
                                             email +
                                             "', '" + firstName +
                                             "', '" + lastName +
                                             "', '" + password +
                                             "')");
            
            if (rv == 1) {
                // TODO: perform a redirect to dashboard
                out.println("Insertion successful.");
            } else {
                // TODO: perform a redirect to registration page with a url-param maybe
                out.println("Insertion failed.");
            }
        } catch(Exception e) {
            out.println(e);
        }
    }
}