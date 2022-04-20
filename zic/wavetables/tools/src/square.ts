import { save, WAVETABLE_SIZE } from './wavetable';

function main() {
    const table = [];
    for (let i = 0; i < WAVETABLE_SIZE + 1; i++) {
        if(i < WAVETABLE_SIZE / 2) {
            table.push('1.0');
        } else {
            table.push('0.0');
        }
    }
    save(table, 'square');
}
main();
