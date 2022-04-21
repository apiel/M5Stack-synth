import { save, WAVETABLE_SIZE } from './wavetable';

function main() {
    const table = [];
    for (let i = 0; i < WAVETABLE_SIZE; i++) {
        const value = Math.sin((Math.PI * i) / WAVETABLE_SIZE);
        table.push(value);
    }
    save(table, 'sine');
}
main();
