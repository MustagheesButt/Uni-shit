<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<t:generic_layout>
    <jsp:attribute name="head">
        <title>History</title>
        <meta name="description" content="View your transaction history." />
    </jsp:attribute>
    <jsp:attribute name="footer">
        <script>
        </script>
    </jsp:attribute>

    <jsp:body>
        <div class="container">
            <div id="notification" class="alert d-none" role="alert"></div>
            <h2 class="text-center mt-3 mb-5">History</h2>
            <p>View your transaction history of both buying and selling stocks.</p>

            <div class="row">
                <table class="table">
                    <thead>
                        <tr>
                            <th scope="col">#</th>
                            <th scope="col">Type</th>
                            <th scope="col">Symbol</th>
                            <th scope="col">Quantity</th>
                            <th scope="col">Price</th>
                            <th scope="col">Date</th>
                        </tr>
                    </thead>
                    <tbody>
                        <c:forEach items="${transactions_data}" var="transaction" varStatus="loop">
                            <tr>      
                                <td>${loop.index + 1}</td>
                                <td>${transaction.type}</td>
                                <td>${transaction.symbol}</td>
                                <td>${transaction.quantity}</td>
                                <td>${transaction.price}</td>
                                <td>${transaction.date}</td>
                            </tr>
                        </c:forEach>
                    </tbody>
                </table>
            </div>
        </div>
    </jsp:body>

    
</t:generic_layout>