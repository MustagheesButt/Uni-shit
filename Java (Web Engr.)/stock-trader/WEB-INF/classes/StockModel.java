public class StockModel {
    public Integer id;
    public String symbol;
    public Integer quantity;

    StockModel(Integer id, String symbol, Integer quantity) {
        this.id = id;
        this.symbol = symbol;
        this.quantity = quantity;
    }

    public Integer getId() {
        return this.id;
    }

    public String getSymbol() {
        return this.symbol;
    }

    public Integer getQuantity() {
        return this.quantity;
    }
}