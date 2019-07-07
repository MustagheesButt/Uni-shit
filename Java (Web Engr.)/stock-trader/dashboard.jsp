<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<t:generic_layout>
    <jsp:attribute name="head">
        <title>Dashboard</title>
        <meta name="description" content="Dashboard. Get quotes, buy and sell stocks." />
    </jsp:attribute>
    <jsp:attribute name="footer">
        <script>
            $("#quoteForm").submit(function (e) {
                e.preventDefault()

                const API_KEY = "TQJI5MB1Y8NE26UC"
                const symbol = $("#symbol").val()

                if (symbol.length == 0) {
                    return;
                }

                // get details
                $.get("https://www.alphavantage.co/query?function=SYMBOL_SEARCH&keywords=" + symbol + "&apikey=" + API_KEY + "&datatype=json", function (data) {
                    const ofConcern = data["bestMatches"][0]

                    if (ofConcern["1. symbol"].toLowerCase() == symbol) {
                        $("#results").removeClass("d-none")
                        console.log(ofConcern)
                        $("#symbol-value").html(ofConcern["1. symbol"])
                        $("#symbol-name").html(ofConcern["2. name"])
                        $("#symbol-currency").html(ofConcern["8. currency"])
                        $("input[name=symbol]").val(ofConcern["1. symbol"])
                        $("input[name=name]").val(ofConcern["2. name"])
                        $("input[name=curr]").val(ofConcern["8. currency"])

                        // get quote
                        $.get("https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + API_KEY + "&datatype=json", function (data) {
                            const quote = data["Global Quote"]

                            $("#symbol-price").html(quote["05. price"] + " " + ofConcern["8. currency"])
                            $("#symbol-volume").html(quote["06. volume"])
                            $("#symbol-change").html(quote["10. change percent"])
                            $("input[name=price]").val(quote["05. price"])
                        })
                    } else {
                        $("#results").addClass("d-none")
                    }
                })
            })

            // statuses
            if (window.location.search.indexOf("buySuccess") !== -1) {
                $("#notification").removeClass("d-none").addClass("alert-success").html("You have bought shares successfully!")
            }
            if (window.location.search.indexOf("buyFail") !== -1) {
                $("#notification").removeClass("d-none").addClass("alert-danger").html("Could not buy shares. Possible cause could be insufficient funds.")
            }
            if (window.location.search.indexOf("sellSuccess") !== -1) {
                $("#notification").removeClass("d-none").addClass("alert-success").html("Sold stock successfully!")
            }
            if (window.location.search.indexOf("sellFail") !== -1) {
                $("#notification").removeClass("d-none").addClass("alert-danger").html("Could not sell stock. Possible cause could be invalid quantity!")
            }
        </script>
    </jsp:attribute>

    <jsp:body>
        <div class="container">
            <div id="notification" class="alert d-none" role="alert"></div>
            <h2 class="text-center mt-3 mb-5">Dashboard</h2>
            
            <div class="row">
                <div class="col-md-6">
                    <div class="row">

                        <form id="quoteForm">
                            <div class="form-group">
                                <label for="symbol">Look for a symbol</label>
                                <input type="text" class="form-control" id="symbol" aria-describedby="symbolHelp" placeholder="Enter a symbol">
                                <small id="symbolHelp" class="form-text text-muted">Search for a symbol like MSFT or AABA.</small>
                            </div>
                            <button type="submit" class="btn btn-primary">Get Quote</button>
                        </form>
                    </div>

                    <div id="results" class="row d-none">
                        <div class="col-md-6">
                            <h5>Symbol</h5>
                            <h3 id="symbol-value"></h3>
                            <h5>Full Name</h5>
                            <h3 id="symbol-name"></h3>
                            <h5>Currency</h5>
                            <h3 id="symbol-currency"></h3>
                        </div>

                        <div class="col-md-6">
                            <h5>Price</h5>
                            <h3 id="symbol-price"></h3>
                            <h5>Volume</h5>
                            <h3 id="symbol-volume"></h3>
                            <h5>Change</h5>
                            <h3 id="symbol-change"></h3>
                        </div>

                        <form action="buy" method="GET">
                            <input type="hidden" name="symbol" />
                            <input type="hidden" name="name" />
                            <input type="hidden" name="price" />
                            <input type="hidden" name="curr" />

                            <button type="submit" class="btn btn-primary">Buy Now</button>
                        </form>
                    </div>
                </div>

                <div class="col-md-6">
                    <div class="row">
                        <div class="col-md-6">
                            <h5>Owned Stocks</h5>
                            <h3>${ total_stock }</h3>
                        </div>

                        <div class="col-md-6">
                            <h5>Your Balance</h5>
                            <h3>${ user_cash } USD</h3>
                        </div>
                    </div>

                    <div class="row">
                        <table class="table">
                            <thead>
                                <tr>
                                    <th scope="col">#</th>
                                    <th scope="col">Symbol</th>
                                    <th scope="col">Stock</th>
                                    <th scope="col">Sell</th>
                                </tr>
                            </thead>
                            <tbody>
                                <c:forEach items="${stocks_data}" var="stock" varStatus="loop">
                                    <tr>      
                                        <td>${loop.index + 1}</td>
                                        <td>${stock.symbol}</td>
                                        <td>${stock.quantity}</td>
                                        <td><a class="btn btn-primary" href="sell?uid=${stock.id}&sym=${stock.symbol}&q=${stock.quantity}">Sell</a></td> 
                                    </tr>
                                </c:forEach>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </jsp:body>

    
</t:generic_layout>