"use strict";
String.prototype.replaceAt = function (index, replacement) {
	return this.substring(0, index) + replacement + this.substring(index + replacement.length);
}
async function fetchAsync (url) {
	let response = await fetch(url)
	.catch(function(error) {
		console.error("Cant find dictionary!");
	})
	let data = await response?.text();
	return data;
}

jQuery(document).ready(async function () {
	const listWords = (await fetchAsync("words.txt")).split('\n').filter(el => {
		return el != "" && el.length == 5 && /^[a-zA-Z]+$/.test(el);
	});
	const tile = $(".tile");

	var currentRow = 0;
	var currentLetter = 0;
	var maxRow = 6;
	var maxLetter = 5;
	var loop = 1;
	const wordsRows = [...new Array(maxRow)].map(x => new Array(maxLetter).fill(''));
	
	const findingWord = listWords[Math.floor(Math.random() * listWords.length)];
	// const findingWord = "banjos";
	console.error(findingWord)

	wordsRows.forEach((e, i) => {
		var wordsRow = $(`<div id="wordsRow-${i}"></div>`);
		tile.append(wordsRow);
		e.forEach((_, i_) => {
			var words = $(`<div id="wordsRow-${i}-${i_}" class="words"></div>`);
			wordsRow.append(words);
		});
	});
	const keyboardA = ["Q", "W", "E", "R", "T","Y", "U", "I", "O", "P", "A", "S", "D", "F", "G", "H", "J", "K", "L", "ENTER", "Z", "X", "C", "V", "B", "N", "M", "←"];
	const keyboard = $(".keyboard");
	keyboardA.forEach((e, i) => {
		var wordsRow = $(`<button class="key" id="${e}">${e}</button>`);
		keyboard.append(wordsRow);
	});



	function addLetter(letter = "") {
		if (currentLetter >= maxLetter || currentRow >= maxRow || letter == "")
			return;
		const letterdiv = $(`#wordsRow-${currentRow}-${currentLetter}`)[0];
		letterdiv.textContent = letter;
		wordsRows[currentRow][currentLetter] = letter;
		// letterdiv.attr("data", letter);
		currentLetter++;
	}
	function removeLetter() {
		if (currentLetter <= 0)
			return;
		currentLetter--;
		const letterdiv = $(`#wordsRow-${currentRow}-${currentLetter}`)[0];
		letterdiv.textContent = '';
		wordsRows[currentRow][currentLetter] = '';
	}

	function flip(doFunc) {
		var tmpRow = currentRow;
		wordsRows[tmpRow].forEach(((e, i) => {
			setTimeout(function () {
				$(`#wordsRow-${tmpRow}-${i}`).addClass("flip");
				setTimeout(function () {
					doFunc(i, e, tmpRow);
				}, 250);
			}, 500 * i);
		}));
	}

	function checkWord() {
		if (currentLetter == maxLetter - 1)
			return;
		var word = wordsRows[currentRow].join('').toLowerCase();
		if (word == findingWord) { // if word is the correct
			flip((i, e) => {
				$(`#wordsRow-${currentRow}-${i}`).addClass("green");
				$(`.keyboard #${e}`).addClass("green");
			});
			$(".title")[0].outerHTML = "<h1>Win !</h1>";
			loop = 0;
			return;
		}
		else {
			if (listWords.includes(word)) { // if word is in dict but not the correct'

				var copyValid = findingWord.toUpperCase();
				var guess = [];
				var tmpRow = currentRow;
				wordsRows[tmpRow].forEach(((e, i) => {
					guess.push({letter: e, color: "grey", lock: false})
				}));
				guess.forEach(((e, i) => {
					if (e.letter == copyValid.charAt(i)) {
						e.color = "green";
						copyValid = copyValid.replaceAt(i, ' ');
						e.lock = true;
					}
				}));
				console.log(guess)
				guess.forEach(((e, i) => {
					if (!e.lock && copyValid.includes(e.letter))
					{
						e.color = "yellow";
						copyValid = copyValid.replace(e.letter, ' ');
						e.lock = true;
					}
				}));
				flip((i, e) => {
					$(`#wordsRow-${tmpRow}-${i}`).addClass(guess[i].color);
					if (!$(`.keyboard #${e}`).attr("class").match(/(yellow|green)/gm))
						$(`.keyboard #${e}`).addClass(guess[i].color);
				});
				currentLetter = 0;
				currentRow++;
			}
		}
		if (currentRow >= maxRow) {
			$(".title")[0].outerHTML = "<h1>Loose..</h1>";
			loop = 0;
			return;
		}
	}
	$(document).on('keydown', function (event) {
		if (!loop)
			return;
		if (event.key == "Enter")
			checkWord();
		else if (event.key == "Backspace")
			removeLetter();
		else if (event.key.match(/[a-zA-Z]/g) && event.key.length == 1)
			addLetter(event.key.toUpperCase())
	});
});
/*
Uncaught ReferenceError: assignment to undeclared variable letter
    removeLetter http://127.0.0.1:5500/nodejs/html/main.js:50
    <anonymous> http://127.0.0.1:5500/nodejs/html/main.js:124
    jQuery 2
        dispatch
        handle
6 main.js:50:3
*/