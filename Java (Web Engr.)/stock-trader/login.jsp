<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags" %>

<t:generic_layout>
    <jsp:attribute name="head">
        <title>Login</title>
        <meta name="description" content="Login now" />
    </jsp:attribute>
    <jsp:attribute name="footer">
        <script>
            if (window.location.search.indexOf("email") !== -1) {
                $("#notification").removeClass("d-none").html("The email is wrong or does not exist!")
            }
            if (window.location.search.indexOf("password") !== -1) {
                $("#notification").removeClass("d-none").html("The password provided is wrong!")
            }
        </script>
    </jsp:attribute>

    <jsp:body>
        <div class="container">
            <h2 class="text-center">Login</h2>
            
            <div class="row justify-content-center">
                <div class="col-md-6">
                    <div id="notification" class="alert alert-danger d-none" role="alert"></div>

                    <form action="login" method="POST">
                        <div class="form-group">
                            <label for="inputEmail1">Email address</label>
                            <input type="email" name="email" class="form-control" id="inputEmail1" aria-describedby="emailHelp" placeholder="Enter email">
                            <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
                        </div>
                        <div class="form-group">
                            <label for="inputPassword1">Password</label>
                            <input type="password" name="password" class="form-control" id="inputPassword1" placeholder="Password">
                        </div>
                        <button type="submit" class="btn btn-primary">Login</button>
                    </form>
                </div>
            </div>
        </div>
    </jsp:body>

    
</t:generic_layout>