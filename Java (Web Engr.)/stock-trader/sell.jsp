<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags" %>

<t:generic_layout>
    <jsp:attribute name="head">
        <title>Sell Stocks</title>
        <meta name="description" content="Sell your owned stocks." />
    </jsp:attribute>
    <jsp:attribute name="footer">
        <script>
            
            query(updateUI)

            // deal with UI
            $("input").on("change input", function (e) {
                updateUI()
            });

            // get current price of the stock
            function query(callback) {
                const API_KEY = "TQJI5MB1Y8NE26UC"
                const symbol = $("#symbol").val()
                

                $.get("https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + API_KEY + "&datatype=json", function (data) {
                    const quote = data["Global Quote"]

                    $("input[name=price]").val(quote["05. price"])

                    callback()
                })
            }

            function updateUI() {
                // calculate total and remaining
                const price    = $("#price").val()
                const quantity = $("#quantity").val()
                const balance  = parseInt($("#curr-balance").html())

                const total = price * quantity
                const after_selling = balance + total

                // update UI
                $("#total").html(total + " USD")
                $("#after-selling").html(after_selling + " USD")
            }
        </script>
    </jsp:attribute>

    <jsp:body>
        <div class="container">
            <h2 class="text-center mt-3 mb-5">Sell Your Stocks & Shares</h2>
            
            <p>Are you sure you want to sell your ${param.name} stock now?</p>
            <form action="sell" method="POST">
                <div class="form-group">
                    <label for="symbol">Symbol</label>
                    <input type="text" name="symbol" class="form-control" id="symbol" value="${ param.sym }" readonly>
                </div>
                <div class="form-group">
                    <label for="price">Price</label>
                    <input type="text" name="price" class="form-control" id="price" value="0" readonly>
                </div>
                <div class="form-group">
                    <label for="quantity">Quantity</label>
                    <input type="number" name="quantity" class="form-control" id="quantity" value="${ param.q }" min="1">
                </div>

                <table class="table">
                    <thead>
                        <tr>
                            <th scope="col">Total</th>
                            <th scope="col">Your Balance</th>
                            <th scope="col">After Selling</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td id="total"></td>
                            <td id="curr-balance">${ current_cash } USD</td>
                            <td id="after-selling"></td>
                        </tr>
                    </tbody>
                </table>
                
                <button type="submit" class="btn btn-primary">Confirm</button>
            </form>
        </div>
    </jsp:body>

    
</t:generic_layout>