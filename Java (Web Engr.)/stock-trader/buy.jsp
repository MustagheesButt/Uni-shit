<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags" %>

<t:generic_layout>
    <jsp:attribute name="head">
        <title>Buy Stocks</title>
        <meta name="description" content="Buy a stock of your choice right now." />
    </jsp:attribute>
    <jsp:attribute name="footer">
        <script>
            $(document).ready(function () {
                updateUI()
            })
            $("input").on("change input", function (e) {
                updateUI()
            });

            function updateUI() {
                // calculate total and remaining
                const price    = $("#price").val()
                const quantity = $("#quantity").val()
                const balance  = parseInt($("#curr-balance").html())

                const total = price * quantity
                const remaining = balance - total

                // update UI
                $("#total").html(total + " USD")
                $("#remaining-balance").html(remaining + " USD")
            }
        </script>
    </jsp:attribute>

    <jsp:body>
        <div class="container">
            <h2 class="text-center mt-3 mb-5">Buy Stocks & Shares</h2>
            
            <p>Buying ${param.name} stock now</p>
            <form action="buy" method="POST">
                <div class="form-group">
                    <label for="symbol">Symbol</label>
                    <input type="text" name="symbol" class="form-control" id="symbol" value="${ param.symbol }" readonly>
                </div>
                <div class="form-group">
                    <label for="price">Price</label>
                    <input type="text" name="price" class="form-control" id="price" value="${ param.price }" readonly>
                </div>
                <div class="form-group">
                    <label for="quantity">Quantity</label>
                    <input type="number" name="quantity" class="form-control" id="quantity" value="1" min="1">
                </div>

                <table class="table">
                    <thead>
                        <tr>
                            <th scope="col">Total</th>
                            <th scope="col">Your Balance</th>
                            <th scope="col">Remaining Balance</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td id="total"></td>
                            <td id="curr-balance">${ current_cash } USD</td>
                            <td id="remaining-balance"></td>
                        </tr>
                    </tbody>
                </table>
                
                <button type="submit" class="btn btn-primary">Confirm</button>
            </form>
        </div>
    </jsp:body>

    
</t:generic_layout>