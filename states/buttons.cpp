void buttons() {
    vector exitRow = {
        Button('q', "¬ыход", [] {exit(0);})
    };
    state1.defineButtons({
        {
            Button('2', "»дти на 2", [] {RenderState(state2);}),
            Button('3', "»дти на 3", [] {RenderState(state3);}),
        },
        {
            Button('4', "»дти на 4", [] {RenderState(state4);}),
            Button('5', "»дти на 5", [] {RenderState(state5);}),
        }, exitRow
    });
    state2.defineButtons({
        {
            Button('1', "»дти на 1", [] {RenderState(state1);}),
            Button('3', "»дти на 3", [] {RenderState(state3);}),
        },
        {
            Button('4', "»дти на 4", [] {RenderState(state4);}),
            Button('5', "»дти на 5", [] {RenderState(state5);}),
        }, exitRow
    });
    state3.defineButtons({
        {
            Button('2', "»дти на 2", [] {RenderState(state2);}),
            Button('1', "»дти на 1", [] {RenderState(state1);}),
        },
        {
            Button('4', "»дти на 4", [] {RenderState(state4);}),
            Button('5', "»дти на 5", [] {RenderState(state5);}),
        }, exitRow
    });
    state4.defineButtons({
        {
            Button('2', "»дти на 2", [] {RenderState(state2);}),
            Button('3', "»дти на 3", [] {RenderState(state3);}),
        },
        {
            Button('1', "»дти на 1", [] {RenderState(state1);}),
            Button('5', "»дти на 5", [] {RenderState(state5);}),
        }, exitRow
    });
    state5.defineButtons({
        {
            Button('2', "»дти на 2", [] {RenderState(state2);}),
            Button('3', "»дти на 3", [] {RenderState(state3);}),
        },
        {
            Button('4', "»дти на 4", [] {RenderState(state4);}),
            Button('1', "»дти на 1", [] {RenderState(state1);}),
        }, exitRow
    });
}