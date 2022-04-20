import { writeFileSync } from 'fs';

export const WAVETABLE_SIZE = 2048;

export function save(table: number[] | string[], name: string) {
    const content = `
#ifndef WAVETABLE_${name.toUpperCase()}_H_
#define WAVETABLE_${name.toUpperCase()}_H_

float wavetableSine[${WAVETABLE_SIZE}] = {${table.join('f, ')}};

#endif
`;
    writeFileSync(`../wavetable_${name}.h`, content);
}
