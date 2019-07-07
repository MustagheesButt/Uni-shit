function sigmoid(x) {
    return 1 / (1 + Math.exp(-x))
}

function dsigmoid(y) {
    return y * (1 - y)
}

function htan(x) {
    return Math.tanh(x)
}

function dhtan(y) {
    return 1 - (y*y)
}

class NeuralNetwork {
    /**
     * @param {number} inputNodes
     * @param {number} hiddenNodes
     * @param {number} outputNodes
     * @param {function} activationFunction
     * @param {function} dActivationFunction - Derivative of the Activation Function.
     */
    constructor(inputNodes, hiddenNodes, outputNodes, activationFunction, dActivationFunction) {
        this.INPUT_NODES         = inputNodes
        this.HIDDEN_NODES        = hiddenNodes
        this.OUTPUT_NODES        = outputNodes
        this.activationFunction  = activationFunction
        this.dActivationFunction = dActivationFunction

        // matrix of weights between input and hidden layer
        this.weights_ih = new Matrix(this.HIDDEN_NODES, this.INPUT_NODES)
        this.weights_ih.randomize()

        // matrix of weights between hidden and output layer
        this.weights_ho = new Matrix(this.OUTPUT_NODES, this.HIDDEN_NODES)
        this.weights_ho.randomize()

        // bias matrices
        this.bias_h = new Matrix(this.HIDDEN_NODES, 1)
        this.bias_h.randomize()
        this.bias_o = new Matrix(this.OUTPUT_NODES, 1)
        this.bias_o.randomize()

        // learning rate
        this.LR = 0.5
    }

    /**
     * 
     * @param {number[]} input 
     */
    feedforward(inputs) {
        inputs = Matrix.fromArray(inputs)
        
        // multiply input with hidden matrix, then add bias
        let hidden = Matrix.multiply(this.weights_ih, inputs)
        hidden.add(this.bias_h)
        hidden = hidden.arr.map(this.activationFunction)
        
        // multiply hidden layer's output with output matrix, then add bias
        let outputs = Matrix.multiply(this.weights_ho, Matrix.fromArray(hidden))
        outputs.add(this.bias_o)
        outputs = outputs.arr.map(this.activationFunction)

        return outputs
    }

    train(inputs, answers) {
        answers = Matrix.fromArray(answers)
        
        /* FEEDFORWARD */
        inputs = Matrix.fromArray(inputs)
        
        // multiply input with hidden matrix, then add bias
        let hidden = Matrix.multiply(this.weights_ih, inputs)
        hidden.add(this.bias_h)
        hidden = Matrix.fromArray(hidden.arr.map(this.activationFunction))
        
        // multiply hidden layer's output with output matrix, then add bias
        let outputs = Matrix.multiply(this.weights_ho, hidden)
        outputs.add(this.bias_o)
        outputs = Matrix.fromArray(outputs.arr.map(this.activationFunction))
        /* FEEDFORWARD ENDS */

        // calculate output layer errors
        const output_errors = Matrix.subtract(answers, outputs)
        //const output_errors = Matrix.mean_sqaured_error(answers, outputs)

        // calculate gradients
        let gradients = Matrix.map(outputs, this.dActivationFunction)
        gradients.multiply(output_errors)
        gradients.multiply(this.LR)

        // calculate hidden->output deltas
        let hidden_t = Matrix.transpose(hidden)
        let weights_ho_deltas = Matrix.multiply(gradients, hidden_t)

        // adjust weights
        this.weights_ho.add(weights_ho_deltas)
        // adjust biases
        this.bias_o.add(gradients)

        // calculate hidden layer errors
        const w_ho_t = Matrix.transpose(this.weights_ho)
        const hidden_errors = Matrix.multiply(w_ho_t, output_errors)

        // calculate hidden gradient
        let hidden_gradient = Matrix.map(hidden, this.dActivationFunction)
        hidden_gradient.multiply(hidden_errors)
        hidden_gradient.multiply(this.LR)

        // calculate input->hidden deltas
        let inputs_t = Matrix.transpose(inputs)
        let weights_ih_deltas = Matrix.multiply(hidden_gradient, inputs_t)

        // adjust weights
        this.weights_ih.add(weights_ih_deltas)
        // adjust biases
        this.bias_h.add(hidden_gradient)
        
    }
}