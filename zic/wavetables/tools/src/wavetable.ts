import { writeFileSync } from 'fs';

export const WAVETABLE_SIZE = 2048;

export function save(table: number[], name: string) {
    const content = `
#ifndef WAVETABLE_${name.toUpperCase()}_H_
#define WAVETABLE_${name.toUpperCase()}_H_

float wavetableSine[${WAVETABLE_SIZE}] = {${table
        .map((val) => (val == 0 || val == 1 ? `${val}.0f` : `${val}f`))
        .join(', ')},};

#endif
`;
    writeFileSync(`../wavetable_${name}.h`, content);
}
