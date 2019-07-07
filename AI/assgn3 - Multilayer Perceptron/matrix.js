class Matrix {
    constructor(rows, cols) {
        this.rows = rows
        this.cols = cols
        this.arr = new Array(this.rows)

        for (var i = 0; i < this.rows; i++) {
            this.arr[i] = new Array(this.cols)
            this.arr[i].fill(0)
        }
    }

    randomize() {
        for (var i = 0; i < this.rows; i++) {
            for (var j = 0; j < this.cols; j++) {
                this.arr[i][j] = (Math.random() * 2) - 1
            }
        }
    }

    add(x) {
        if (!(x instanceof Matrix)) {
            console.error("Argument needs to be of type Matrix!")
            return
        }
        if (this.rows !== x.rows || this.cols !== x.cols) {
            console.error("Dimensions of the matrices must be same for addition!")
            return
        }

        for (var i = 0; i < this.rows; i++) {
            for (var j = 0; j < this.cols; j++) {
                this.arr[i][j] += x.arr[i][j]
            }
        }
    }

    static subtract(x, y) {
        if (!(x instanceof Matrix) || !(y instanceof Matrix)) {
            console.error("Arguments needs to be of type Matrix!")
            return
        }
        if (x.rows !== y.rows || x.cols !== y.cols) {
            console.error("Dimensions of the matrices must be same for subtraction!")
            return
        }

        const result = new Matrix(x.rows, x.cols)
        for (var i = 0; i < x.rows; i++) {
            for (var j = 0; j < x.cols; j++) {
                result.arr[i][j] = x.arr[i][j] - y.arr[i][j]
            }
        }

        return result
    }

    /**
     * 
     * @param {Matrix} answers 
     * @param {Matrix} outputs 
     */
    static mean_sqaured_error(x, y) {
        if (!(x instanceof Matrix) || !(y instanceof Matrix)) {
            console.error("Arguments needs to be of type Matrix!")
            return
        }
        if (x.rows !== y.rows || x.cols !== y.cols) {
            console.error("Dimensions of the matrices must be same for MSE!")
            return
        }

        // calculate MSE
        let mse = 0

        for (var i = 0; i < x.rows; i++) {
            for (var j = 0; j < x.cols; j++) {
                const error = x.arr[i][j] - y.arr[i][j]
                mse += (error**2)
            }
        }

        mse = mse * 0.5

        const result = new Matrix(x.rows, x.cols)
        for (var i = 0; i < x.rows; i++) {
            for (var j = 0; j < x.cols; j++) {
                result.arr[i][j] =  y.arr[i][j] - mse
            }
        }

        return result
    }

    // standard matrix multiplication
    static multiply(a, b) {
        if (!(a instanceof Matrix) || !(b instanceof Matrix)) {
            console.error("Both arguments must be matrices!")
            return
        }
        if (a.cols !== b.rows) {
            console.error("Invalid dimensions for matrix dot product!")
            return
        }

        var matrix = new Matrix(a.rows, b.cols)

        for (var i = 0; i < a.rows; i++) {
            for (var j = 0; j < b.cols; j++) {
                var sum = 0
                for (var k = 0; k < a.cols; k++) {
                    sum += (a.arr[i][k] * b.arr[k][j])
                }

                matrix.arr[i][j] = sum
            }
        }

        return matrix
    }

    // element-wise and scalar multiplication
    multiply(a) {
        // element-wise
        if (a instanceof Matrix) {
            for (var i = 0; i < this.rows; i++) {
                for (var j = 0; j < this.cols; j++) {
                    this.arr[i][j] *= a.arr[i][j]
                }
            }
        } else {
            for (var i = 0; i < this.rows; i++) {
                for (var j = 0; j < this.cols; j++) {
                    this.arr[i][j] *= a
                }
            }
        }
    }

    static transpose(x) {
        const result = new Matrix(x.cols, x.rows)
        for (var i = 0; i < x.rows; i++) {
            for (var j = 0; j < x.cols; j++) {
                result.arr[j][i] = x.arr[i][j]
            }
        }

        return result
    }

    static fromArray(array) {
        const rows = array.length
        const cols = array[0].length || 1
        const matrix = new Matrix(rows, cols)

        for (var i = 0; i < rows; i++) {
            for (var j = 0; j < cols; j++) {
                matrix.arr[i][j] = array[i][j] || array[i + j]
            }
        }

        return matrix
    }

    toArray() {
        let arr = []

        for (var i = 0; i < this.rows; i++) {
            for (var j = 0; j < this.cols; j++) {
                arr.push(this.arr[i][j])
            }
        }

        return arr
    }

    static map(x, func) {
        let result = new Matrix(x.rows, x.cols)

        for (var i = 0; i < x.rows; i++) {
            for (var j = 0; j < x.cols; j++) {
                result.arr[i][j] = func(x.arr[i][j])
            }
        }

        return result
    }

    print() {
        console.table(this.arr)
    }
}