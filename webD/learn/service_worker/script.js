const worker = new Worker('worker.js')
const sumBtn =document.getElementById('sumBtn')
const bgBtn = document.getElementById('bgBtn')

sumBtn.addEventListener("click", (e) => {
	console.log('Summation Process Started...')
	sumBtn.disabled = true;
	worker.postMessage('Hello, Worker')
});

worker.onmessage = function(message) {
	console.log(message.data)
	sumBtn.disabled = false;
}

bgBtn.addEventListener("click", (e) => {
	console.log('Change Background')
});