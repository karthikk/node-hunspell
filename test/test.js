var spell = require('./spell');

console.log(spell.isValidWord('test'))
console.log(spell.isValidWord('toast'))
console.log(spell.isValidWord('triskd'))
console.log(spell.isValidWord('dementeed'))
console.log(spell.isValidWord('flickr'))
console.log(spell.isValidWord('longbowmun'))

console.log(spell.suggest('test'))
console.log(spell.suggest('toast'))
console.log(spell.suggest('triskd'))
console.log(spell.suggest('dementeed'))
console.log(spell.suggest('flickr'))
console.log(spell.suggest('longbowmun'))
