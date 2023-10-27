onmessage = function (message) {
	let sum =0;
	for (let i=0; i<1e10; i++)
		sum +=i;

	this.postMessage(sum)
}