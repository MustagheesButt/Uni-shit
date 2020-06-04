<%@tag description="Overall Page template" pageEncoding="UTF-8"%>

<%@attribute name="head" fragment="true" %>
<%@attribute name="footer" fragment="true" %>

<html>
    <head>
        <jsp:invoke fragment="head"/>

        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- Bootstrap CSS -->
        <link rel="stylesheet" href="static/css/bootstrap.min.css">
    </head>
  <body>
    <nav class="navbar navbar-expand-lg navbar-light bg-light">
        <a class="navbar-brand" href="#">StockTrader</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
        </button>

        <div class="collapse navbar-collapse" id="navbarSupportedContent">
            <ul class="navbar-nav mr-auto">
                <% if (session.getAttribute("user_id") != null) { %>
                <li class="nav-item">
                    <a class="nav-link" href="dashboard">Dashboard <span class="sr-only">(current)</span></a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="history">History</a>
                </li>
                <% } else { %>
                <li class="nav-item">
                    <a class="nav-link" href="login">Login</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="register">Register</a>
                </li>
                <% } %>
            </ul>

            <% if (session.getAttribute("user_id") != null) { %>
            <ul class="navbar-nav mr-5">
                <li class="nav-item">
                    <span class="navbar-text">Welcome, <%= session.getAttribute("user_name") %></span>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="logout">Logout</a>
                </li>
            </ul>
            <% } %>
        </div>
    </nav>

    <div id="body">
        <jsp:doBody/>
    </div>

    <script src="static/js/jquery-3.3.1.min.js"></script>
    <script src="static/js/popper.min.js"></script>
    <script src="static/js/bootstrap.min.js"></script>

    <jsp:invoke fragment="footer"/>

    <footer class="container">
        <p>&copy; Copyright 2019. All rights reserved.</p>
    </footer>
  </body>
</html>