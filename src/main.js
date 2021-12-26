import Vue from 'vue'
import App from './App.vue'

import VueRouter from 'vue-router'
import router from './router/index'
import vuetify from './plugins/vuetify'
import { store } from "./store/store";
Vue.use(VueRouter)

Vue.config.productionTip = false

new Vue({
  store: store,
  router,
  vuetify,
  render: h => h(App)
}).$mount('#app')
