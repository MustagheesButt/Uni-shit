let nn
let mnist
let train_index = 0

let VIEW_TOCOLOR
let VIEW_LABEL
let VIEW_GUESS
let VIEW_PERCENTAGE

function setup() {
    VIEW_TOCOLOR    = document.querySelector('.to-color')
    VIEW_LABEL      = document.querySelector('#label')
    VIEW_GUESS      = document.querySelector('#guess')
    VIEW_PERCENTAGE = document.querySelector('#perc')

    createCanvas(400, 400).parent('container')

    nn = new NeuralNetwork(784, 64, 10, sigmoid, dsigmoid)

    loadMNIST(function (data) {
        mnist = data
        console.log(mnist)
    })
}

function draw() {
    background(50)

    if (mnist) {
        train()
        //noLoop()    
    }
}

function train() {
    let inputs = []
    let img = createImage(28, 28)

    img.loadPixels()
    for (var i = 0; i < 784; i++) {
        let bright = mnist.train_images[train_index][i]
        inputs[i] = bright/255
        
        let index = i * 4
        
        img.pixels[index + 0] = bright
        img.pixels[index + 1] = bright
        img.pixels[index + 2] = bright
        img.pixels[index + 3] = 255
    }
    img.updatePixels()

    image(img, 200, 0, 200, 200)

    let label = mnist.train_labels[train_index]
    let targets = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    targets[label] = 1
    

    let predictions = nn.feedforward(inputs)
    let guess       = findMaxIndex(predictions)
    let perc        = (train_index / 60000) * 100

    // update UI
    VIEW_LABEL.innerHTML = label
    VIEW_GUESS.innerHTML = guess
    VIEW_PERCENTAGE.innerHTML = perc.toFixed(3) + " %"

    if (label == guess) {
        VIEW_TOCOLOR.classList = 'correct'
    } else {
        VIEW_TOCOLOR.classList = 'wrong'
    }

    // actuall neural network training
    nn.train(inputs, targets)

    train_index = (train_index + 1) % mnist.train_labels.length
}

function findMaxIndex(arr) {
    let max = -1
    let maxIndex = 0

    for (var i = 0; i < arr.length; i++) {
        if (arr[i] > max) {
            max = arr[i]
            maxIndex = i
        }
    }

    return maxIndex
}