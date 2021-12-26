import Vue from "vue";
import Vuex from "vuex";
import VuexPersistence from "vuex-persist";

// Import the plugin module here

const initialState = () => ({
    isLogged: false,
    testando: 'hello world'
});

Vue.use(Vuex);
const vuexLocal = new  VuexPersistence ({
    storage: window.localStorage,
    reducer: (state) => ({
        isLogged: state.isLogged,
    }),
});

export const store = new Vuex.Store({
    plugins: [vuexLocal.plugin],
    getters: {
        
    },
    state: initialState,
    // first call action
    actions: {
        setLogged(context, value) {
            context.commit("updateLogged", value);
        },
    },
    //after call mutation
    mutations: {
        updateLogged(state, value) {
            state.isLogged = value;
        },
    },
});
