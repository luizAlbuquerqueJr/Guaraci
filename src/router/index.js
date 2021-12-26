import Vue from 'vue'
import VueRouter from 'vue-router'
import routes from './routes' // imported the file with all the routes

Vue.use(VueRouter) // vue now knows we're using VueRouter

var router = new VueRouter({ // the instance of VueRouter
    mode: 'history', // its mode
    routes // the routes
})

export default router // export it so we can use it on other files