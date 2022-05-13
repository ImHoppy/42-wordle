jQuery(document).ready(function(){
	const tile = $(".tile");

	var currentRow = 0;
	var currentLetter = 0;
	var maxRow = 6;
	var maxLetter = 5;
	var loop = 1;
	const wordsRows = [...new Array(maxRow)].map(x => new Array(maxLetter).fill(''));
	// const wordsRows = [
	// 	['', '', '', '', ''],
	// 	['', '', '', '', ''],
	// 	['', '', '', '', ''],
	// 	['', '', '', '', ''],
	// 	['', '', '', '', ''],
	// 	['', '', '', '', '']
	// ];
	wordsRows.forEach((e, i) => {
		var wordsRow = $(`<div id="wordsRow-${i}"></div>`);
		tile.append(wordsRow);
		e.forEach((_, i_) => {
			var words = $(`<div id="wordsRow-${i}-${i_}" class="words"></div>`);
			wordsRow.append(words);
		});
	});

	function addLetter(letter = "") {
		if (currentLetter >= maxLetter || currentRow >= maxRow || letter == "")
			return ;
		const letterdiv = $(`#wordsRow-${currentRow}-${currentLetter}`)[0];
		letterdiv.textContent = letter;
		wordsRows[currentRow][currentLetter] = letter;
		// letterdiv.attr("data", letter);
		currentLetter++;
	}
	function removeLetter() {
		if (currentLetter <= 0)
			return ;
		currentLetter--;
		letter = '';
		const letterdiv = $(`#wordsRow-${currentRow}-${currentLetter}`)[0];
		letterdiv.textContent = letter;
		wordsRows[currentRow][currentLetter] = letter;
	}
	function checkWord() {
		if (currentLetter != maxLetter - 1)
		var word = wordsRows[currentRow].join('').toLocaleLowerCase();
		const wordDiv = $(`#wordsRow-${currentRow}`);
		if (word == "valid") { // if word is the correct
			$(".title")[0].outerHTML = "<h1>Win !</h1>";
			console.log(word)
			wordDiv.children('div').addClass("flip");
			wordDiv.children('div').addClass("green");
			loop = 0;
		}
		else {
			if (currentRow >= maxRow) {
				$(".title")[0].outerHTML = "<h1>Loose..</h1>";
				loop = 0;
			}
			else if (true) { // if word is in dict but not the correct

				currentLetter = 0;
				currentRow++;
			}
		}
	}
	$(document).on('keydown',function(event) {
		if (!loop)
			return;
		console.log(event.key)
		if (event.key == "Enter")
			checkWord();
		else if (event.key == "Backspace")
			removeLetter();
		else if (event.key.match(/[a-zA-Z]/g) && event.key.length == 1)
			addLetter(event.key.toUpperCase())
	});
});