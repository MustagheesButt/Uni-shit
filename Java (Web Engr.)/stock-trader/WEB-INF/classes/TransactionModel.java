import java.sql.Date;

public class TransactionModel {
    public Integer id;
    public String type;
    public String symbol;
    public Integer quantity;
    public Double price;
    public Date date;

    TransactionModel(Integer id, String type, String symbol, Integer quantity, Double price, Date date) {
        this.id       = id;
        this.type     = type;
        this.symbol   = symbol;
        this.quantity = quantity;
        this.price    = price;
        this.date     = date;
    }

    public Integer getId() {
        return this.id;
    }

    public String getType() {
        return this.type;
    }

    public String getSymbol() {
        return this.symbol;
    }

    public Integer getQuantity() {
        return this.quantity;
    }

    public Double getPrice() {
        return this.price;
    }

    public Date getDate() {
        return this.date;
    }
}