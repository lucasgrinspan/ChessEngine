var board =[[' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
            [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ']];
var moveList = [];
var isPieceSelected = false;
var isPieceBeingHeld = false;
var HTMLPieceText;
var previousTileElement;
var selectedPiece;
var windowOffset = [0, 0];
function generateCoordsFromTileNum(tileNumber) {
    y = String(Math.floor(tileNumber / 8));
    x = String(tileNumber % 8);
    return y + x;
}
//  Generate move list
function logMove(previousSquare, currentSquare) {
    moveList.push(previousSquare + currentSquare);
}
function getPieceList() {
    var pieceList = "";
    for (var i = 0; i < 8; i++) {
        for (var j = 0; j < 8; j++) {
            if (board[i][j] != ' ') {
                pieceList += (board[i][j] + String(i) + String(j));
            }
        }
    }
    return pieceList;
}
//  Displays the green circles over the board indicating possible moves
function displayTiles() {
}
function applyEventHandlers(target) {
    target.onmousedown = selectPiece;
    target.onmousemove = dragPiece;
    target.onmouseup = dropPiece;
}
//  For debugging
function generateBoard() {
    //  Clear board
    for (var i = 0; i < 8; i++) {
        for (var j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
    var pieces = document.getElementsByClassName("piece");
    //  Reads board from application into array
    for (var i = 0; i < pieces.length; i++) {
        var tileNumber = parseInt(pieces[i].parentElement.id.slice(5));
        var pieceIcon = pieces[i].id;
        board[Math.floor(tileNumber / 8)][tileNumber % 8] = pieceIcon;
    }
    // for (var i = 0; i < 8; i++) {
    //     var boardString = "";
    //     for (var j = 0; j < 8; j++) {
    //         boardString += (board[i][j] + " ");
    //     }
    //     console.log(boardString);
    //     boardString = "";
    // }
}
function movePiece() {
    if (isPieceSelected) {
        isPieceSelected = false;
        event.target.innerHTML = HTMLPieceText;
        previousTileElement.innerHTML = "";
        applyEventHandlers(event.target.firstElementChild)
        var previouseTile = generateCoordsFromTileNum(parseInt(previousTileElement.id.slice(5)));
        var currentTile = generateCoordsFromTileNum(parseInt(event.target.id.slice(5)));
        logMove(previouseTile, currentTile);
        generateBoard();
    }
}
function selectPiece() {
    //  Stops propogation of pieces
    if (!event) var event = window.event;
    event.cancelBubble = true;
    if (event.stopPropagation) event.stopPropagation();

    isPieceBeingHeld = true;
    selectedPiece = event.target;
    previousTileElement = event.target.parentElement;
    HTMLPieceText = selectedPiece.parentElement.innerHTML;
    windowOffset = [
        selectedPiece.offsetLeft - event.clientX,
        selectedPiece.offsetTop - event.clientY
    ];
    selectedPiece.style.position = "absolute";
}
function dragPiece() {
    event.preventDefault();
    if (isPieceBeingHeld) {
        mousePosition = {

            x : event.clientX,
            y : event.clientY

        };
        selectedPiece.style.left = (mousePosition.x + windowOffset[0]) + 'px';
        selectedPiece.style.top  = (mousePosition.y + windowOffset[1]) + 'px';
    }
}
function dropPiece() {
    if (isPieceBeingHeld) {
        isPieceBeingHeld = false;
        var newTileElement = document.elementsFromPoint(event.clientX, event.clientY)[1];
        //  If the tiles are the same, then emulate a click
        var previousePiece = document.elementsFromPoint(event.clientX, event.clientY)[0];
        previousTileElement.innerHTML = "";
        newTileElement.innerHTML = HTMLPieceText;
        applyEventHandlers(newTileElement.childNodes[0]);
        
        if (newTileElement == previousTileElement) {
            isPieceSelected = true;
        } else {
            var previouseTile = generateCoordsFromTileNum(parseInt(previousTileElement.id.slice(5)));
            var currentTile = generateCoordsFromTileNum(parseInt(newTileElement.id.slice(5)));
            logMove(previouseTile, currentTile);
            generateBoard();
        }
    }
}

var pieces = document.getElementsByClassName("piece");
for (var i = 0; i < pieces.length; i++) {
    pieces[i].onmousedown = selectPiece;
    pieces[i].onmousemove = dragPiece;
    pieces[i].onmouseup = dropPiece;
}
var tiles = document.getElementsByClassName("tile")
for (var i = 0; i < tiles.length; i++) {
    tiles[i].onclick = movePiece;
}
generateBoard();
console.log(getPieceList())
const Evaluator = require('./build/Release/Evaluator');
console.log(Evaluator.sum());