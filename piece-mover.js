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
function displayGreenCircle(tileNumber) {
    var tile = document.getElementById("tile" + tileNumber)
    if (tile.innerHTML == "") {
        tile.innerHTML = "<svg class='green-circle-svg' id='circle" + tileNumber + "' onclick='movePiece()' onmouseover='greenCircleHover(true)' onmouseleave='greenCircleHover(false)' viewBox='0 0 50 50' height='50' width='50' xmlns='http://www.w3.org/2000/svg'><circle class='circle' cx='25' cy='25' r='7' fill='rgba(17, 132, 0, 0.73)' style='pointer-events:none;'/></svg>";
    } else {
        tile.innerHTML += "<svg class='green-circle-svg' id='circle" + tileNumber + "' onclick='movePiece()' onmouseover='greenCircleHover(true)' onmouseleave='greenCircleHover(false)' viewBox='0 0 50 50' height='50' width='50' xmlns='http://www.w3.org/2000/svg'><rect class='rect' width='50' height='50' fill='transparent' style='pointer-events:none;'/></svg>";
    }
}
function greenCircleHover(display) {
    circle = event.target.childNodes[0].getAttribute("class") == "circle";
    if (circle) {
        if (display) {
            event.target.childNodes[0].setAttribute('r', '10');
        } else {
            event.target.childNodes[0].setAttribute('r', '7');
        }
    //  If its the overlay for taking a piece    
    } else {
        if (display) {
            event.target.childNodes[0].setAttribute('style', 'stroke-width:9px;pointer-events:none;');
        } else {
            event.target.childNodes[0].setAttribute('style', 'stroke-width:7px;pointer-events:none;');
        }
    }
}
function clearGreenCircles() {
    var circles = document.getElementsByClassName("green-circle-svg");
    var limit = circles.length;
    while (circles.length > 0){
        circles[0].parentNode.removeChild(circles[0]);
    }
}
function generateCoordsFromTileNum(tileNumber) {
    y = String(Math.floor(tileNumber / 8));
    x = String(tileNumber % 8);
    return y + x;
}
function generateTileNumFromCoords(coords) {
    var y = parseInt(coords[0]);
    var x = parseInt(coords[1]);
    var tileNumber = (y * 8) + x;
    return String(tileNumber)
}
function getPossibleMoves(pieceCoords) {
    var possibleMoves = Evaluator.generatePossibleMoves();
    var possibleMovesForTile = [];
    for (var i = 0; i < possibleMoves.length; i++) {
        if (pieceCoords == possibleMoves[i].substring(0, 2)) {
            possibleMovesForTile.push(possibleMoves[i].slice(2));
        }
    }
    return possibleMovesForTile
}
//  Update the board in the C++ file
function updateAddonBoard(from, to) {
    return Evaluator.updateBoard(from + to)
}
function applyOpponentMove() {
    var move = Evaluator.getOpponentMove();
    var from = generateTileNumFromCoords(move.substring(0, 2));
    var to = generateTileNumFromCoords(move.substring(2, 4));
    var HTMLPiece = document.getElementById("tile" + from).innerHTML;
    document.getElementById("tile" + from).innerHTML = "";
    document.getElementById("tile" + to).innerHTML = HTMLPiece;
    console.log(move);
}
//  Generate move list
function logMove(previousSquare, currentSquare) {
    updateAddonBoard(previousSquare + currentSquare);
    generateBoard();
    moveList.push(previousSquare + currentSquare);
    console.log(previousSquare + currentSquare);
    setTimeout(applyOpponentMove, 100);
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
function applyEventHandlers(target) {
    target.onmousedown = selectPiece;
    target.onmousemove = dragPiece;
    target.onmouseup = dropPiece;
}
function clearMove() {
    clearGreenCircles();
    isPieceBeingHeld = false;
    isPieceSelected = false;
}
//  For debugging and undo operator
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
        var tileNumber = parseInt(pieces[i].parentElement.id.slice(4));
        var pieceIcon = pieces[i].id;
        board[Math.floor(tileNumber / 8)][tileNumber % 8] = pieceIcon;
    }
}
function movePiece() {
    if (isPieceSelected) {
        isPieceSelected = false;
        var tile = event.target.parentElement;
        tile.innerHTML = HTMLPieceText;
        previousTileElement.innerHTML = "";
        applyEventHandlers(tile.firstElementChild)
        var previousTile = generateCoordsFromTileNum(parseInt(previousTileElement.id.slice(4)));
        var currentTile = generateCoordsFromTileNum(parseInt(tile.id.slice(4)));
        logMove(previousTile, currentTile);
        clearGreenCircles();
    }
}
function selectPiece() {
    //  Stops propogation of event to tile
    if (!event) var event = window.event;
    event.cancelBubble = true;
    if (event.stopPropagation) event.stopPropagation();

    clearGreenCircles();

    //  Generates possible moves to display as an overlay on the board
    var pieceCoords = generateCoordsFromTileNum(event.target.parentElement.id.slice(4));
    var possibleTiles = getPossibleMoves(pieceCoords);
    var greenCircleHTML = document.getElementById("green-circle-wrapper");
    for (var i = 0; i < possibleTiles.length; i++) {
        //  Convert from coordinates to tile number and creates the image
        displayGreenCircle((possibleTiles[i][0] * 8) + (possibleTiles[i][1] % 8))
    }

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
        
        var onValidTile;
        if (newTileElement.getAttribute("class") == "green-circle-svg") {
            onValidTile = true;
            newTileElement = newTileElement.parentElement;
        } else if (newTileElement.getAttribute("class") == "circle") {
            onValidTile = true;
            newTileElement = newTileElement.parentElement.parentElement;
        }
        var validMove = onValidTile && 
                        ((newTileElement.firstElementChild.getAttribute("class") == "green-circle-svg") ||
                        newTileElement.childNodes.length > 1);
        var sameTile = (newTileElement == previousTileElement);

        if (validMove || sameTile) {
            var previousePiece = document.elementsFromPoint(event.clientX, event.clientY)[0];
            previousTileElement.innerHTML = "";
            newTileElement.innerHTML = HTMLPieceText;
            applyEventHandlers(newTileElement.childNodes[0]);
            
            //  If the tiles are the same, then emulate a click
            if (sameTile) {
                isPieceSelected = true;
            } else {
                var previouseTile = generateCoordsFromTileNum(parseInt(previousTileElement.id.slice(4)));
                var currentTile = generateCoordsFromTileNum(parseInt(newTileElement.id.slice(4)));
                logMove(previouseTile, currentTile);
                clearGreenCircles();
            }
        } else {
            clearGreenCircles();
            isPieceBeingHeld = false;
            //  Reset piece back to original tile
            previousTileElement.innerHTML = HTMLPieceText;
            applyEventHandlers(previousTileElement.childNodes[0]);
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
    tiles[i].onclick = clearMove;
}
generateBoard();
const Evaluator = require('./build/Release/Evaluator');
